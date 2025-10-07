#include "SceneLoader.h"

void SceneLoader::LoadFile(std::string file) {

  std::string filePath = directoryPath_ + file + ".json";

  std::ifstream path = CLEYERA::FileLoader::JsonLoadFile(filePath);
  path >> deserialized;
  assert(deserialized.is_object());
  assert(deserialized.contains("name"));
  assert(deserialized["name"].is_string());

  // sceneじゃなかった時エラーを吐く
  std::string name = deserialized["name"].get<std::string>();
  assert(name.compare("scene") == 0);

  // 読み込み開始
  for (nlohmann::json &object : deserialized["objects"]) {
    assert(object.contains("type"));

    std::string type = object["type"].get<std::string>();

    if (type.compare("MESH") == 0) {
      LoadobjData(object);
    }
  }
}

std::vector<std::weak_ptr<UtilGameObject>> SceneLoader::SettingData() {
  auto objManager = CLEYERA::Manager::ObjectManager::GetInstance();
  const auto &objsMap = objManager->GetObjects();

  std::vector<std::shared_ptr<UtilGameObject>> enviObjs;
  std::vector<std::weak_ptr<UtilGameObject>> resultEnviObjs;

  for (const auto &[category, nameMap] : objsMap) {
    for (const auto &[name, obj] : nameMap) {
      if (!obj)
        continue;

      auto itData = objDatas_.find(name);
      if (itData != objDatas_.end()) {
        const auto &data = itData->second;

        obj->SetScale(data.scale);
        obj->SetRotate(data.rotate);
        obj->SetTranslate(data.translate);
        objManager->GetCategoryData(category).ChangeModelData(data.modeHandle_);
        obj->SetIsTerrainHit(data.isTerrainHit);
        obj->SetIsGravity(data.isGravity_);

        auto gameObj = obj->GetGameObject().lock();
        if (gameObj) {
          for (const auto &parentName : data.parentObjName_) {
            for (const auto &[_, innerMap] : objsMap) {
              for (const auto &[_a, potentialParent] : innerMap) {
                if (potentialParent &&
                    potentialParent->GetName() == parentName) {
                  gameObj->SetParent(potentialParent->GetGameObject());
                  break;
                }
              }
            }
          }
        }

        objDatas_.erase(itData);
      }
    }
  }

  // 残ったobjDatas_に対して新しくEnvironmentObjectを作成
  for (const auto &[name, data] : objDatas_) {
    
      std::string category = this->RemoveNumberSuffix(name);

      auto obj = objManager
                   ->CreateObject<UtilGameObject>(
                       category, std::make_shared<UtilGameObject>())
                   .lock();

    // 各種データを反映
    obj->SetScale(data.scale);
    obj->SetRotate(data.rotate);
    obj->SetTranslate(data.translate);
    objManager->GetCategoryData(category).ChangeModelData(data.modeHandle_);
    obj->SetIsTerrainHit(data.isTerrainHit);
    obj->SetIsGravity(data.isGravity_);

    // 親設定
    auto gameObj = obj->GetGameObject().lock();
    if (gameObj) {
      for (const auto &parentName : data.parentObjName_) {
        for (const auto &[_, innerMap] : objsMap) {
          for (const auto &[_a, potentialParent] : innerMap) {
            if (potentialParent && potentialParent->GetName() == parentName) {
              gameObj->SetParent(potentialParent->GetGameObject());
              break;
            }
          }
        }
      }
    }

    enviObjs.push_back(obj);
    resultEnviObjs.push_back(obj); // weakにして返却リストに追加
  }

  // objDatas_を空にする（処理済なので）
  objDatas_.clear();

  return resultEnviObjs;
}

SceneObjData SceneLoader::LoadobjData(nlohmann::json object, SceneObjData data,
                                      std::string name) {
  SceneObjData newData{};
  // insか通常
  std::string drawType = object["DrawType"].get<std::string>();
  // object名前
  std::string objectName = object["name"].get<std::string>();


  std::string categoryName = this->RemoveNumberSuffix(objectName);

  categoryObjectSize_[categoryName]++;

  uint32_t modelHandle = 0;

  if (name != "") {
    newData.parentObjName_.push_back(name);
  }

  // モデルのパスの受け取り
  if (object.contains("Directory_name")) {
    newData.modelDirectoryPath = object["Directory_name"].get<std::string>();
  }
  if (object.contains("file_name")) {
    newData.modelName = object["file_name"].get<std::string>();
  }

  if (object.contains("gravity_Flag")) {
    newData.isGravity_ = object["gravity_Flag"].get<bool>();
  }
  if (object.contains("terrain_Flag")) {
    newData.isGravity_ = object["terrain_Flag"].get<bool>();
  }

  if (newData.modelName != "" && newData.modelDirectoryPath != "") {
    modelHandle = CLEYERA::Manager::ModelManager::GetInstance()->LoadModel(
        newData.modelDirectoryPath, newData.modelName);
  }

  // 座標
  nlohmann::json &transform = object["transform"];
  Math::Vector::Vec3 translate, rotate, scale;
  translate.x = (float)transform["translate"][0];
  translate.y = (float)transform["translate"][2];
  translate.z = (float)transform["translate"][1];

  // rotate
  rotate.x = -(float)transform["rotate"][0];
  rotate.y = -(float)transform["rotate"][2];
  rotate.z = -(float)transform["rotate"][1];

  // scale
  scale.x = (float)transform["scale"][0];
  scale.y = (float)transform["scale"][2];
  scale.z = (float)transform["scale"][1];

  rotate.x = Math::Vector::Func::degreesToRadians(rotate.x);
  rotate.y = Math::Vector::Func::degreesToRadians(rotate.y);
  rotate.z = Math::Vector::Func::degreesToRadians(rotate.z);

  newData.scale = scale;
  newData.rotate = rotate;
  newData.translate = translate;
  newData.modeHandle_ = modelHandle;

  // 子の読み込み
  if (object.contains("children")) {
    nlohmann::json &child = object["children"];
    for (size_t i = 0; i < child.size(); i++) {
      std::string childType = child[i]["type"].get<std::string>();

      if (childType.compare("MESH") == 0) {
        this->LoadobjData(child[i], newData, objectName);
      }
    }
  }

  objDatas_[objectName] = newData;

  return {};
}

std::string SceneLoader::RemoveNumberSuffix(const std::string &key) {
  int i = static_cast<int>(key.size()) - 1;
  // 後ろから数字を探す
  while (i >= 0 && std::isdigit(key[i])) {
    --i;
  }
  // 末尾に .数字 が付いているか確認
  if (i >= 0 && key[i] == '.' && i < static_cast<int>(key.size()) - 1) {
    return key.substr(0, i); // "." の前まで残す
  }
  return key; // ".数字" が無ければそのまま返す
}

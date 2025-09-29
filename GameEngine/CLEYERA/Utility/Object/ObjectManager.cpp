#include "ObjectManager.h"

using json = nlohmann::json;
using OBJ_MODE = CLEYERA::Component::ObjectComponent::OBJ_MODE;
void CLEYERA::Util::system::InstancingObjectData::ChangeModelData(uint32_t modelHandle_) {

  modelHandle = modelHandle_;
  model = CLEYERA::Manager::ModelManager::GetInstance()->GetModel(modelHandle_);
}

void CLEYERA::Manager::ObjectManager::Update() {

  for (const auto &m : this->objects_) {
    for (auto &[name, obj] : m.second) {
      if (!obj)
        continue;

      switch (obj->GetMode()) {
      case OBJ_MODE::SPAWN: {
        auto gravity = Manager::GravityManager::GetInstance();
        auto terrain = Manager::Terrain::GetInstance();

        obj->Init();
        obj->SetMode(OBJ_MODE::ACTIVE);
        obj->Update();
        obj->GameObjectUpdate();

        if (obj->GetIsGravity())
          gravity->PushData(obj);

        if (obj->GetIsTerrainHit())
          terrain->PushData(obj);

        break;
      }

      case OBJ_MODE::REMOVE: {
        obj->Finalize();
        // 削除対象
        DeleteObject(obj);
        break;
      }

      case OBJ_MODE::PAUSE: {
        // 一時停止中なので何もしない（Update済み）
        obj->GameObjectUpdate();
        break;
      }

      case OBJ_MODE::INACTIVE: {
        // 完全に非アクティブなのでスキップ
        // 必要なら Update() 呼ばない方が良い
        break;
      }

      case OBJ_MODE::ACTIVE: {
        obj->Update();
        obj->GameObjectUpdate();
        break;
      }
      }
    }
  }
}

void CLEYERA::Manager::ObjectManager::ImGuiUpdate() {

  ImGui::Begin("オブジェクト管理");

  for (const auto &m : objects_) {

    if (m.first == "") {
      return;
    }
    if (ImGui::TreeNode(m.first.c_str())) {

      for (const auto &obj : m.second) {

        if (!obj.second) {
          continue;
        }
        obj.second->ImGuiUpdate();
      }
      ImGui::TreePop();
    }
  }

  ImGui::End();
}

void CLEYERA::Manager::ObjectManager::Draw() {
  auto piplineManager_ = Graphics::Raster::RasterPiplineManager::GetInstance();
  auto cameraManager_ = Manager::CameraManager::GetInstance();
  auto lightManager = Manager::LightManager::GetInstance();
  auto texManager_ = Manager::TexManager::GetInstance();
  auto commandManager_ = Base::DX::DXCommandManager::GetInstace();

  piplineManager_->SetRootsignature(Graphics::RasterPipline_Mode3d::DF_MODEL3d);
  piplineManager_->SetPipline(Graphics::RasterPipline_Mode3d::DF_MODEL3d);

  for (auto &data : instancingData_) {
    auto &it = data.second;

    cameraManager_->BindCommand(0);

    it.worldIns->Command(1);

    auto data = texManager_->GetTexData(it.model.lock()->GetAlbedoTexHandle());
    auto handle = Base::DX::DXDescripterManager::GetInstance()->GetSRVGPUHandle(data.lock()->GetSrvIndex());
    commandManager_->GraphicsDescripterTable(2, handle);

    lightManager->DirectionLightCommandBind(3);

    cameraManager_->BindCommand(4);

    it.MaterialIns->Command(5);
    // 頂点、インデックス、形状設定
    it.model.lock()->RasterDraw3d();

    commandManager_->DrawIndexCall(UINT(it.model.lock()->GetMeshData()->GetData().indecs.size()), it.max);
  }
}

void CLEYERA::Manager::ObjectManager::LoadObjectData(const std::string &file) {
  const std::string filePath = "Resources/Configs/SceneObjectNum/" + file;

  Clear();

  std::ifstream ifs(filePath);
  if (!ifs) {
    std::cerr << "Failed to open file: " << file << std::endl;
    return;
  }

  json jsonRoot;
  ifs >> jsonRoot;

  // グループ名（例: "test"）を指定// ファイル名（例:
  // "test.json"）から拡張子を除去
  std::string groupName = file;
  size_t dotPos = groupName.rfind('.');
  if (dotPos != std::string::npos) {
    groupName = groupName.substr(0, dotPos);
  }

  // JSON内でグループ名を検索
  auto itGroup = jsonRoot.find(groupName);
  if (itGroup == jsonRoot.end() || !itGroup->is_object()) {
    std::cerr << "Group not found or invalid format: " << file << std::endl;
    return;
  }

  for (auto &[name, value] : itGroup->items()) {
    if (!value.is_array() || value.size() != 2 || !value[0].is_string() || !value[1].is_number_unsigned()) {
      std::cerr << "Invalid object format for key: " << name << std::endl;
      continue;
    }

    ObjectNumData data;
    data.key = value[0].get<std::string>();
    data.objNum = value[1].get<uint32_t>();

    for (uint32_t i = 0; i < data.objNum; ++i) {
      std::string fullName = data.key;
      if (i > 0) {
        std::ostringstream oss;
        oss << "." << std::setfill('0') << std::setw(3) << i;
        fullName += oss.str();
      }

      // 登録
      objects_[name][fullName] = nullptr;

      unUseObjsName_[name].push_back(fullName);
    }

    this->CreateInstancing(name, data.objNum);
  }
}

void CLEYERA::Manager::ObjectManager::DeleteObject(std::weak_ptr<Component::ObjectComponent> obj) {
  if (!obj.lock())
    return;

  const std::string &name = obj.lock()->GetName();
  const std::string &category = obj.lock()->GetCategory();

  // 名前を unUse に戻す
  unUseObjsName_[category].push_back(name);

  auto itCat = objects_.find(category);
  if (itCat != objects_.end()) {
    auto &nameMap = itCat->second;
    auto itName = nameMap.find(name);
    if (itName != nameMap.end()) {
      int num = this->ExtractNumber(name);
      this->instancingData_[category].worldIns->DelateData(num);
      this->instancingData_[category].worldData[name] = nullptr;
      this->instancingData_[category].MaterialData[name] = nullptr;

      this->instancingData_[category].MaterialIns->DelateData(num);
      itName->second.reset();
    }
  }
}

void CLEYERA::Manager::ObjectManager::ObjectRegister(const std::string &category, const size_t &size, std::shared_ptr<CLEYERA::Component::ObjectComponent> obj) {

  // カテゴリが存在しない場合、自動で128個作成
  auto itCategory = unUseObjsName_.find(category);
  if (itCategory == unUseObjsName_.end()) {
    for (uint32_t i = 0; i < size; ++i) {
      std::string fullName = category;
      if (i > 0) {
        std::ostringstream oss;
        oss << "." << std::setfill('0') << std::setw(3) << i;
        fullName += oss.str();
      }

      // 登録
      objects_[category][fullName] = nullptr;

      unUseObjsName_[category].push_back(fullName);
    }

    // instancingでーた作成
    this->CreateInstancing(category, size);
  }

  // 使用可能名がないならエラー
  if (unUseObjsName_[category].empty()) {
    std::cerr << "No available object names for category: " << category << std::endl;
  }

  itCategory = unUseObjsName_.find(category);
  std::string name = itCategory->second.front();
  itCategory->second.erase(itCategory->second.begin());

  obj->SetName(name);
  obj->SetCategory(category);
  // 登録
  objects_[category][name] = std::move(obj);
  instancingData_[category].worldData[name] = &objects_[category][name]->GetGameObject().lock()->GetWorldData();
  instancingData_[category].MaterialData[name] = &objects_[category][name]->GetColorData();

  int32_t number = ExtractNumber(name);
  instancingData_[category].worldIns->SetWorldData(instancingData_[category].worldData[name], number);
  instancingData_[category].MaterialIns->SetWorldData(instancingData_[category].MaterialData[name], number);

  // 名前とカテゴリを設定
  // obj->SetModelHandle(&instancingData_[category].modelHandle);

}

void CLEYERA::Manager::ObjectManager::CreateInstancing(const std::string &category, uint32_t size) {

  instancingData_[category].max = size;
  if (!instancingData_[category].model.lock())
    instancingData_[category].model = ModelManager::GetInstance()->GetModel(0);
  instancingData_[category].MaterialIns = std::make_unique<Model3d::InstancingMaterial>();
  instancingData_[category].MaterialIns->Init(instancingData_[category].max);
  instancingData_[category].worldIns = std::make_unique<Model3d::InstancingWorld>();
  instancingData_[category].worldIns->Init(instancingData_[category].max);
}

int CLEYERA::Manager::ObjectManager::ExtractNumber(const std::string &key) {
  int i = (int)key.size() - 1;
  // 後ろから数字を探す
  while (i >= 0 && std::isdigit(key[i])) {
    --i;
  }
  if (i == (int)key.size() - 1) {
    return 0; // 数字が無ければ 0
  }
  std::string numStr = key.substr(i + 1);
  return std::stoi(numStr);
}

#include "GlobalVariables.h"

namespace fs = std::filesystem;

void CLEYERA::Manager::GlobalVariables::CreateGroup(
    const ResourcesGroupDirectory &d, const std::string &name,
    std::string file) {
  datas_[name];

  if (d == ResourcesGroupDirectory::Entitiys) {
    datas_[name].DirectryPath = "Resources/Configs/Entitiys/" + file + "/";
  }
  if (d == ResourcesGroupDirectory::UI) {
    datas_[name].DirectryPath = "Resources/Configs/UI/" + file + "/";
  }

  else {
    datas_[name].DirectryPath = file;
  }
}

void CLEYERA::Manager::GlobalVariables::SaveFile(const std::string &groupName) {
  using Vector2 = Math::Vector::Vec2;
  using Vector3 = Math::Vector::Vec3;
  using Vector4 = Math::Vector::Vec4;

  // グループを検索
  std::map<std::string, Group>::iterator itGroup = datas_.find(groupName);

  // 未登録チェック
  assert(itGroup != datas_.end());

  nlohmann::json root;
  root = nlohmann::json::object();

  // jsonオブジェクトの登録
  root[groupName] = nlohmann::json::object();
  // 各項目について
  auto &goupItem = itGroup->second;
  for (std::map<std::string, Item>::iterator itItem = goupItem.items.begin();
       itItem != goupItem.items.end(); ++itItem) {
    // 項目名を取得
    const std::string &itemName = itItem->first;
    // 項目の参照を取得
    Item &item = itItem->second;

    // int32_tの値を保持している場合
    if (std::holds_alternative<int32_t>(item.value)) {
      // int32_tの値の登録
      root[groupName][itemName] = std::get<int32_t>(item.value);
    } // floatの値を保持している場合
    else if (std::holds_alternative<float>(item.value)) {
      // floatの値の登録
      root[groupName][itemName] = std::get<float>(item.value);
    } // Vector2の値を保持している場合
    if (std::holds_alternative<Vector2>(item.value)) {
      // Vector2の値の登録
      Vector2 value = std::get<Vector2>(item.value);
      root[groupName][itemName] = nlohmann::json::array({value.x, value.y});
    } // Vector3の値を保持している場合
    if (std::holds_alternative<Vector3>(item.value)) {
      // Vector3の値の登録
      Vector3 value = std::get<Vector3>(item.value);
      root[groupName][itemName] =
          nlohmann::json::array({value.x, value.y, value.z});
    } // Vector4の値を保持している場合
    if (std::holds_alternative<Vector4>(item.value)) {
      // Vector4の値の登録
      Vector4 value = std::get<Vector4>(item.value);
      root[groupName][itemName] =
          nlohmann::json::array({value.x, value.y, value.z, value.w});
    }
  }

  std::string directoryPath = datas_[groupName].DirectryPath;

  // ディレクトリがなければ作成する
  std::filesystem::path dir(directoryPath);
  if (!std::filesystem::exists(directoryPath)) {
    std::filesystem::create_directory(directoryPath);
  }

  // 書き込むJSONファイルのフルパスを合成する
  std::string filePath = directoryPath + groupName + ".json";

  // 書き込み用ファイルストリーム
  std::ofstream ofs{};
  // ファイルを書き込みように開く
  ofs.open(filePath);

  // ファイルオープン失敗？
  if (ofs.fail()) {
    std::string message = "Failed open data file for write.";
    MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
    assert(0);
    return;
  }
  // ファイルにjson文字列を書き込む(インデント幅4)
  ofs << std::setw(4) << root << std::endl;
  ofs.close();
}

void CLEYERA::Manager::GlobalVariables::LoadFile(
    const std::string &DirectoryPath, const std::string &groupName) {
  using Vector2 = Math::Vector::Vec2;
  using Vector3 = Math::Vector::Vec3;
  using Vector4 = Math::Vector::Vec4;

  // 読み込むJSONファイルのフルパスを合成する
  std::string filePath = DirectoryPath;
  // 読み込み用ファイルストリーム
  std::ifstream ifs;
  // ファイルを読み込み用に開く
  ifs.open(filePath);

  // ファイルオープン失敗?
  if (ifs.fail()) {
    std::string message = "Failed open data file for write.";
    MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
    assert(0);
    return;
  }

  nlohmann::json root;

  ifs >> root;
  ifs.close();

  // グループを検索
  nlohmann::json::iterator itGroup = root.find(groupName);

  // 未登録チェック
  assert(itGroup != root.end());
  // 各アイテムについて
  for (nlohmann::json::iterator itItem = itGroup->begin();
       itItem != itGroup->end(); ++itItem) {
    // アイテム名を取得
    const std::string &itemName = itItem.key();
    Group &group = datas_[groupName];
    group.DirectryPath = DirectoryPath;

    // int32_tの値を保持している場合
    if (itItem->is_number_integer()) {
      // int型の値を登録
      int32_t value = itItem->get<int32_t>();
      SetValue(groupName, itemName, value);
    } // floatの値を保持している場合
    else if (itItem->is_number_float()) {
      // double型の値を登録
      double value = itItem->get<double>();
      SetValue(groupName, itemName, static_cast<float>(value));
    } else if (itItem->is_boolean()) {
      bool value = itItem->get<bool>();
      SetValue(groupName, itemName, static_cast<bool>(value));
    } // 要素数2の配列の場合
    else if(itItem->is_array() && itItem->size() == 2 &&
          (*itItem)[0].is_number_float() && (*itItem)[1].is_number_float()) {
        
      // float型の値を登録
      Vector2 value = {itItem->at(0).get<float>(), itItem->at(1).get<float>()};
      SetValue(groupName, itemName, value);
    } // 要素数3の配列の場合
    else if (itItem->is_array() && itItem->size() == 3) {
      // float型の値を登録
      Vector3 value = {itItem->at(0), itItem->at(1), itItem->at(2)};
      SetValue(groupName, itemName, value);
    } // 要素数4の配列の場合
    else if (itItem->is_array() && itItem->size() == 4) {
      // float型の値を登録
      Vector4 value = {itItem->at(0), itItem->at(1), itItem->at(2),
                       itItem->at(3)};
      SetValue(groupName, itemName, value);
    }
  }
}

void CLEYERA::Manager::GlobalVariables::LoadFiles(
    const std::string &DirectoryPath) {

  std::vector<fs::path> allFiles;
  std::string DirectoryfilePath = "Resources/" + DirectoryPath;

  for (const auto &entry :
       fs::recursive_directory_iterator(DirectoryfilePath)) {
    if (fs::is_regular_file(entry.path())) {
      allFiles.push_back(entry.path());
    }
  }

  for (auto data : allFiles) {
    // ファイルパスを取得
    const std::filesystem::path &filePath = data;

    // ファイル拡張子を取得
    std::string extension = filePath.extension().string();
    // .jsonファイル以外はスキップ
    if (extension.compare(".json") != 0) {
      continue;
    }
    LoadFile(data.string(), filePath.stem().string());
  }
}

void CLEYERA::Manager::GlobalVariables::Update() {}

void CLEYERA::Manager::GlobalVariables::ImGuiUpdate(const std::string name) {

  using Vector2 = Math::Vector::Vec2;
  using Vector3 = Math::Vector::Vec3;
  using Vector4 = Math::Vector::Vec4;

  auto &data = datas_[name];

  if (ImGui::TreeNode("json")) {

    // 各項目について
    for (std::map<std::string, Item>::iterator itItem = data.items.begin();
         itItem != data.items.end(); ++itItem) {
      // 各項目を取得
      const std::string &itemName = itItem->first;
      // 項目の参照を取得
      Item &item = itItem->second;
      // int32_tの値を保持している場合
      if (std::holds_alternative<int32_t>(item.value)) {
        int32_t *ptr = std::get_if<int32_t>(&item.value);
        ImGui::DragInt(itemName.c_str(), ptr, 0, 100);
      } // floatの値を保持している場合
      else if (std::holds_alternative<float>(item.value)) {
        float *ptr = std::get_if<float>(&item.value);
        ImGui::DragFloat(itemName.c_str(), ptr, 0, 100);
      } // bool値
      else if (std::holds_alternative<bool>(item.value)) {
        bool *ptr = std::get_if<bool>(&item.value);
        ImGui::Checkbox(itemName.c_str(), ptr);
      } // Vector2の値を保持している場合
      else if (std::holds_alternative<Vector2>(item.value)) {
        Vector2 *ptr = std::get_if<Vector2>(&item.value);
        ImGui::DragFloat2(itemName.c_str(), reinterpret_cast<float *>(ptr),
                          -10.0f, 10.0f);
      } // Vector3の値を保持している場合
      else if (std::holds_alternative<Vector3>(item.value)) {
        Vector3 *ptr = std::get_if<Vector3>(&item.value);
        ImGui::DragFloat3(itemName.c_str(), &ptr->x, -0.10f, 0.1f);
      } // Vector4の値を保持している場合
      else if (std::holds_alternative<Vector4>(item.value)) {
        Vector4 *ptr = std::get_if<Vector4>(&item.value);
        ImGui::ColorEdit4(itemName.c_str(), reinterpret_cast<float *>(ptr));
      }
    }

    ImGui::Separator();

    // 改行
    if (ImGui::Button("Save")) {
      SaveFile(name);
    }
    ImGui::TreePop();
  }
}

#pragma once
#include "../../pch/Pch.h"

namespace CLEYERA {

namespace Manager {

class GlobalVariables {
public:
  static GlobalVariables *GetInstance() {
    static GlobalVariables ins;
    return &ins;
  };

  enum class ResourcesGroupDirectory {
    SceneData = 0,
    Entitiys = 1,
    UI = 2,
    Item = 3
  };

  /// <summary>
  /// グループ作成
  /// </summary>
  /// <param name="ファイルパスの切替"></param>
  /// <param name="ファイルの名前"></param>
  void CreateGroup(
      const ResourcesGroupDirectory &d = ResourcesGroupDirectory::Entitiys,
      const std::string &name = "", std::string file = "");

  /// <summary>
  /// ファイルに書き出し
  /// </summary>
  /// <param name="groupName"></param>
  void SaveFile(const std::string &groupName);

  /// <summary>
  /// ファイルから読み込む
  /// </summary>
  void LoadFile(const std::string &DirectoryPath, const std::string &groupName);

  /// <summary>
  /// ディレクトリの全ファイル読み込み
  /// </summary>
  void LoadFiles(const std::string &DirectoryPath);

  /// <summary>
  /// 更新処理
  /// </summary>
  void Update();

  /// <summary>
  /// 入力した文字列の中にprefixの文字列があるか
  /// </summary>
  /// <param name="input"></param>
  /// <param name="prefix"></param>
  /// <returns></returns>
  bool StartsWith(const std::string &input, const std::string &prefix) {
    return input.find(prefix) == 0;
  }

  void ImGuiUpdate(const std::string name);

  /// <summary>
  /// dataの中を削除
  /// </summary>
  void Clear() { datas_.clear(); }

#pragma region Get
  bool GetIsSave() { return isSave_; }

  template <typename T>
  T GetValue(const std::string &groupName, const std::string &key);

  std::vector<std::string> GetAllDataKey();

#pragma endregion

#pragma region Set
  template <typename T>
  void SetValue(const std::string &groupName, const std::string &key, T value);
  template <typename T>
  void AddItem(const std::string &groupName, const std::string &key, T value);

#pragma endregion

private:
#pragma region Singleton
  GlobalVariables() = default;
  ~GlobalVariables() = default;
  GlobalVariables(const GlobalVariables &obj) = delete;
  GlobalVariables &operator=(const GlobalVariables &obj) = delete;
#pragma endregion

  void WriteVector3(std::string name, Math::Vector::Vec3 &T);

  // 項目
  struct Item {
    // 項目の値
    std::variant<int32_t, float, bool, Math::Vector::Vec2, Math::Vector::Vec3,
                 Math::Vector::Vec4>
        value;
  };
  // グループ
  struct Group {
    std::map<std::string, Item> items;
    std::string DirectryPath = "";
  };
  // 全データ
  std::map<std::string, Group> datas_;

  // グローバル変数の保存先ファイルパス
  std::string kDirectoryPath = "Resources/GlobalVariables/";

  bool isUseDirectryPath_ = false;

  bool isSave_;

  std::vector<std::string> changeSceneLoadFilePaths_{};
};

template <typename T>
inline T GlobalVariables::GetValue(const std::string &groupName,
                                   const std::string &key) {
  // 指定したグループが存在するかをassertで確認
  assert(datas_.find(groupName) != datas_.end());

  // 指定したグループの参照を取得
  Group &group = datas_[groupName];

  // 指定したキーが存在するかをassertで確認
  assert(group.items.find(key) != group.items.end());

  // 指定したグループから指定したキーの値を取得して返す
  return std::get<T>(group.items[key].value);
}

template <typename T>
inline void GlobalVariables::SetValue(const std::string &groupName,
                                      const std::string &key, T value) {
  // グループの参照を取得
  Group &group = datas_[groupName];
  // 新しい項目のデータを設定
  Item newItem{};
  newItem.value = value;
  // 設定した項目をstd::mapに追加
  group.items[key] = newItem;
}

template <typename T>
inline void GlobalVariables::AddItem(const std::string &groupName,
                                     const std::string &key, T value) {
  // 指定したグループの参照を取得
  Group &group = datas_[groupName];
  // 項目が未登録なら
  if (group.items.find(key) == group.items.end()) {
    SetValue(groupName, key, value);
  }
}

} // namespace Manager
} // namespace CLEYERA

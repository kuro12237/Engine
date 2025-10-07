#pragma once
#include "DFBlock/NormalBlock.h"

struct BlockSizeData {
  std::string name = "";
  size_t size = 0;
};

/// <summary>
/// ブロック管理クラス
/// </summary>
class BlockManager {
public:
  BlockManager() {
    objManager_ = CLEYERA::Manager::ObjectManager::GetInstance();
  };
  ~BlockManager() {};

  void Init();

  void Update();

  void SetGetCategorySizeFunc(std::function<size_t(std::string)> func) {
    GetCategorySizeFunc_ = func;
  }

private:
  std::function<size_t(std::string)> GetCategorySizeFunc_;

  /// <summary>
  /// objctのインスタンス数に応じて作る関数
  /// </summary>
  template <typename T>
  void CreateBlock(BlockSizeData data);


  CLEYERA::Manager::ObjectManager *objManager_ = nullptr;

  std::unordered_map<std::string, std::list<std::weak_ptr<BlockBase>>> blocks_;
  std::list<BlockSizeData> blockSize_;

  const std::map<std::string, size_t> *p_CategoryObjectSize_;
};


template <typename T>
inline void BlockManager::CreateBlock(BlockSizeData data) {

  for (size_t i = 0; i < static_cast<size_t>(data.size); i++) {
    auto obj = objManager_->CreateObject<T>(data.name, std::make_shared<NormalBlock>());
    blocks_[data.name].push_back(obj);
  }
}

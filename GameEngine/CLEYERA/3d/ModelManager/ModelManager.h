#pragma once

#include "../../pch/Pch.h"
#include "Model3dPool.h"

#include "Graphics/TexManager/TexManager.h"

namespace CLEYERA {

namespace Manager {

/// <summary>
/// モデル管理クラス
/// </summary>
class ModelManager {
 public:
   static ModelManager *GetInstance();

   /// <summary>
   /// モデル読み込み
   /// </summary>
   /// <param name="ファイル"></param>
   /// <param name="ファイルの名前(objつけない)"></param>
   /// <returns></returns>
   [[nodiscard]]
   uint32_t LoadModel(const std::string &directory, const std::string fileName);



   /// <summary>
   /// モデルのデータをゲット
   /// </summary>
   /// <param name="key"></param>
   /// <returns></returns>
   [[nodiscard]]
   std::weak_ptr<Model3d::Model> GetModel(std::string key) {
      return datas_[key]->GetModel();
   }

   /// <summary>
   /// モデルのデータをゲット
   /// </summary>
   /// <param name="key"></param>
   /// <returns></returns>
   [[nodiscard]]
   std::weak_ptr<Model3d::Model> GetModel(uint32_t key);

   void Init();

   void Finalize();

 private:
   std::map<std::string, std::unique_ptr<Model3d::system::Model3dPool>> datas_;

   uint32_t handle_ = 0;

   TexManager *texManager_ = nullptr;

#pragma region Singlton
   ModelManager() = default;
   ~ModelManager() = default;
   ModelManager(const ModelManager &) = delete;
   ModelManager &operator=(const ModelManager &) = delete;
#pragma endregion
};

} // namespace Manager

} // namespace CLEYERA
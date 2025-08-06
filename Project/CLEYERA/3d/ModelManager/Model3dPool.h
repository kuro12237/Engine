#pragma once
#include "../Model3d.h"

namespace CLEYERA {
namespace Model3d {
namespace system {

/// <summary>
/// ModelManagerで読み込んだモデルの保存クラス
/// </summary>
class Model3dPool {
 public:
   Model3dPool() {};
   ~Model3dPool() {};

   void SetModel(std::shared_ptr<Model> m) { model_ = std::move(m); }
   void SetKey(const std::string name) { key_ = name; }
   void SetHandle(uint32_t handle) { handle_ = handle; }
  
   std::weak_ptr<Model> GetModel() { return model_; }
   std::string GetKey() { return key_; }
   uint32_t GetHandle() { return handle_; }

 private:
   std::string key_ = "";
   uint32_t handle_ = 0;

   std::shared_ptr<Model3d::Model> model_ = nullptr;
};

} // namespace system
} // namespace Model3d
} // namespace CLEYERA
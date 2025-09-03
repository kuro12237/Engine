#pragma once
#include "Mesh/MeshData.h"

namespace CLEYERA {
namespace Model3d {

/// <summary>
/// モデルクラス
/// </summary>
class Model {
 public:
   Model() {};
   ~Model() {};

   void Init();

   void Update();

   void RasterDraw3d();

   void ImGuiUpdate();

   void CreateMesh(aiMesh *mesh) {
      mesh_ = std::make_unique<Model3d::MeshData>();
      mesh_->Create(mesh);
   }

#pragma region Set
   void SetTexHandle(uint32_t handle) { texHandle_ = handle; }
#pragma endregion

#pragma region Get
   MeshData *GetMeshData() { return mesh_.get(); }
   uint32_t GetTexHandle() { return texHandle_; }
#pragma endregion

 private:
   uint32_t texHandle_ = 0;
   std::unique_ptr<MeshData> mesh_ = nullptr;

   Base::DX::DXCommandManager *commandManager_ = nullptr;
};

} // namespace Model3d
} // namespace CLEYERA
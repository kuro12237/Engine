#pragma once
#include "../../DX/DXBufferResource/DXBufferResource.h"
#include "../../DX/DXManager.h"

#include "../../DX/DXBarrier/DXBarrier.h"
#include "../Game3dObject.h"

namespace CLEYERA {
namespace Model3d {
namespace system {

class Tlas {
 public:
   Tlas() {};
   ~Tlas() {};

   void Init();

   void Update(std::vector<std::weak_ptr<Model3d::Game3dObject>> &obj);

   void BufferBind();

   void SetCreateObject(std::vector<std::weak_ptr<Model3d::Game3dObject>> &obj);

#pragma region Set

#pragma endregion

 private:
   std::vector<D3D12_RAYTRACING_INSTANCE_DESC> instanceDesc_;

   std::unique_ptr<CLEYERA::Base::DX::DXBufferResource<int32_t>> instanceDescBuf;
   std::unique_ptr<Base::DX::DXBufferResource<int32_t>> buf_ = nullptr;
};

} // namespace system
} // namespace Model3d
} // namespace CLEYERA
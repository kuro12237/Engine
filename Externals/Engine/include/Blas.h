#pragma once
#include "../../DX/DXBarrier/DXBarrier.h"
#include "../../DX/DXManager.h"
#include "../../pch/Pch.h"

namespace CLEYERA {
namespace Model3d {
namespace system {

class Blas {
 public:
   Blas() {};
   ~Blas() {};

   void Init();

   void Update();

   void SetSize(uint32_t size) { size_ = size; }
   void SetParamCount(size_t count) { paramCount_ = count; };
   void SetVertexBuf(ID3D12Resource *buf) { vertexbuf_ = buf; }

#pragma region Get

   ID3D12Resource *GetResource() { return buf_->GetResource(); }
#pragma endregion

 private:
   ID3D12Device5 *device_ = nullptr;

   uint32_t size_ = 0;
   size_t paramCount_ = 0;

   ID3D12Resource *vertexbuf_;

   std::unique_ptr<Base::DX::DXBufferResource<int32_t>> buf_;
};

} // namespace system
} // namespace Model3d
} // namespace CLEYERA
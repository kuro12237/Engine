#pragma once
#pragma once
#include "../DXComponent.h"
#include "DXDescripterComponent.h"

namespace CLEYERA {
namespace Base {
namespace DX {

using Microsoft::WRL::ComPtr;

class DXDSVDescripter : public DXDescripterComponent {
 public:
   DXDSVDescripter(const std::string &name) : DXDescripterComponent(name) {};
   ~DXDSVDescripter() {};

   void Create() override;

   size_t AddPtr(ID3D12Resource *buf, D3D12_DEPTH_STENCIL_VIEW_DESC desc);

   void Release(size_t index) { indexFreeList_.push_back(index); }

 private:
   ID3D12Device5 *device_ = nullptr;
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA
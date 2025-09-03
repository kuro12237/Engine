#pragma once
#include "../DXComponent.h"
#include "DXDescripterComponent.h"

namespace CLEYERA {
namespace Base {
namespace DX {

using Microsoft::WRL::ComPtr;

class DXSRVDescripter : public DXDescripterComponent {
 public:
   DXSRVDescripter(const std::string &name) : DXDescripterComponent(name) {};
   ~DXSRVDescripter() {};

   void Create() override;

   [[nodiscard]]
   size_t AddSRVPtr();

   [[nodiscard]]
   size_t AddSRVCreatePtr(ID3D12Resource *buf, D3D12_SHADER_RESOURCE_VIEW_DESC desc);

   [[nodiscard]]
   size_t AddUAVPtr(ID3D12Resource *buf, D3D12_UNORDERED_ACCESS_VIEW_DESC desc);

   void Release(size_t index) { indexFreeList_.push_back(index); }

 private:
   ID3D12Device5 *device_ = nullptr;
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA
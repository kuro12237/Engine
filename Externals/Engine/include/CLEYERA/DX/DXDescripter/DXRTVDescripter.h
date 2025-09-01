#pragma once
#include "../DXComponent.h"
#include "DXDescripterComponent.h"

namespace CLEYERA {
namespace Base {
namespace DX {

using Microsoft::WRL::ComPtr;

class DXRTVDescripter : public DXDescripterComponent {
public:
  DXRTVDescripter(const std::string &name) : DXDescripterComponent(name) {};
  ~DXRTVDescripter() {};

  void Create() override;

  size_t AddPtr(ID3D12Resource*buf,D3D12_RENDER_TARGET_VIEW_DESC desc);

  void Release(size_t index) { indexFreeList_.push_back(index); }

private:

  ID3D12Device5 *device_ = nullptr;
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA
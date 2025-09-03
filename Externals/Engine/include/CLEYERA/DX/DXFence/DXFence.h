#pragma once
#include "../DXComponent.h"

namespace CLEYERA {
namespace Base {
namespace DX {

using Microsoft::WRL::ComPtr;

class DXFence : public DXComponent {
public:
  DXFence(std::string name) : DXComponent(name) {};
  ~DXFence() {};

  void Create() override;

  void End();


private:
  ID3D12Device *device_ = nullptr;
  ID3D12CommandQueue *commandQueue_ = nullptr;

  ComPtr<ID3D12Fence> fence_ = nullptr;
  uint64_t fenceValue = {};
  HANDLE fenceEvent_ = {};
};

} // namespace DX
} // namespace Base
} // namespace CLEYERA
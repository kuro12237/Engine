#pragma once
#include "../../pch/Pch.h"

namespace CLEYERA {
namespace Base {
namespace DX {

class DXManager;


class DXBarrier {
public:
  DXBarrier() {};
  ~DXBarrier() {};

  void Init(size_t barrierSize = 1);

  void Barrier();

#pragma region Set
  void SetBarrierSize(size_t size) { barrierSize_ = size; }
  void SetBarrierState(size_t index, const D3D12_RESOURCE_STATES &before,
                       const D3D12_RESOURCE_STATES &after);
  void SetBarrierFlag(size_t index, const D3D12_RESOURCE_BARRIER_FLAGS &f) {
    barrier_.Flags = f;
    index;
  }
  void SetBarrierType(size_t index, const D3D12_RESOURCE_BARRIER_TYPE &type) {
    barrier_.Type = type;
    index;
  }
  void SetBuffer(ID3D12Resource *buf) { buf_ = buf; }
#pragma endregion

private:
  size_t barrierSize_ = 1;
  D3D12_RESOURCE_BARRIER barrier_{};
  ID3D12Resource *buf_ = nullptr;

  DXManager *dxManager_ = nullptr;
  ID3D12GraphicsCommandList *commandList_ = nullptr;
};

} // namespace DX
} // namespace Base
} // namespace CLEYERA
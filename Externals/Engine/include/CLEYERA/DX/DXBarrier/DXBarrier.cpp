#include "DXBarrier.h"
#include "../DXManager.h"

void CLEYERA::Base::DX::DXBarrier::Init(size_t barrierSize) {
  dxManager_ = DXManager::GetInstance();
  commandList_ = dxManager_->GetCommandList();
  barrierSize_ = barrierSize;
}

void CLEYERA::Base::DX::DXBarrier::Barrier() {
  //UINT Num = static_cast<UINT>(barrierSize_);
  barrier_.Transition.pResource = this->buf_;
  commandList_->ResourceBarrier(1, &barrier_);
}

void CLEYERA::Base::DX::DXBarrier::SetBarrierState(
    size_t index, const D3D12_RESOURCE_STATES &before,
    const D3D12_RESOURCE_STATES &after) {
  index;
  barrier_.Transition.StateBefore = before;
  barrier_.Transition.StateAfter = after;
}

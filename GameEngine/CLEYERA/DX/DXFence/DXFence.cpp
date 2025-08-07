#include "DXFence.h"
#include "../DXManager.h"

void CLEYERA::Base::DX::DXFence::Create() {
  dxManager_ = DXManager::GetInstance();
  device_ = dxManager_->GetDevice();
  commandQueue_ = dxManager_->GetCommandQueue();

  device_->CreateFence(fenceValue, D3D12_FENCE_FLAG_NONE,
                       IID_PPV_ARGS(&fence_));
  fenceEvent_ = CreateEvent(NULL, FALSE, FALSE, NULL);
  assert(fenceEvent_ != nullptr);
}

void CLEYERA::Base::DX::DXFence::End() {

  fenceValue++;
  commandQueue_->Signal(fence_.Get(), fenceValue);
  if (fence_->GetCompletedValue() < fenceValue) {
    fenceEvent_ = CreateEvent(NULL, FALSE, FALSE, NULL);
    assert(fenceEvent_ != nullptr);
    fence_->SetEventOnCompletion(fenceValue, fenceEvent_);
    WaitForSingleObject(fenceEvent_, INFINITE);
    CloseHandle(fenceEvent_);
  }
}

#include "DXCommandQueue.h"
#include "../DXManager.h"

void CLEYERA::Base::DX::DXCommandQueue::Create() {
  HRESULT hr;

  dxManager_ = DXManager::GetInstance();
  ID3D12Device5 *device = dxManager_->GetDevice();

  hr = device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue_));
  assert(SUCCEEDED(hr));

  NotifyObserversCreateComp();
}
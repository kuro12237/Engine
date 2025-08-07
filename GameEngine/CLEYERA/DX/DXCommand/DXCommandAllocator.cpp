#include "DXCommandAllocator.h"
#include"../DXManager.h"


void CLEYERA::Base::DX::DXCommandAllocator::Create()
{
  dxManager_ = DXManager::GetInstance();
  ID3D12Device5 *device = dxManager_->GetDevice();

  HRESULT hr;
  hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
                                          IID_PPV_ARGS(&commandAllocator_));
  assert(SUCCEEDED(hr));

  NotifyObserversCreateComp();
}
#include "DXCommandList.h"
#include"../DXManager.h"

void CLEYERA::Base::DX::DXCommandList::Create()
{
  HRESULT hr;

  dxManager_ = DXManager::GetInstance();
  ID3D12Device5 *device = dxManager_->GetDevice();
  
  ID3D12CommandAllocator *allocator = dxManager_->GetCommandAllocator();


  hr = device->CreateCommandList(
      0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator, nullptr,
      IID_PPV_ARGS(&commandlist_));
  assert(SUCCEEDED(hr));

  NotifyObserversCreateComp();
}

void CLEYERA::Base::DX::DXCommandList::End()
{


}

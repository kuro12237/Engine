#include "DXInfoQueue.h"
#include"../DXManager.h"

void CLEYERA::Base::DX::DXInfoQueue::Create()
{
  dxManager_ = DXManager::GetInstance();
  ID3D12Device5 *device = dxManager_->GetDevice();

  if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&infoQueue_)))) {
    infoQueue_->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
    infoQueue_->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
    infoQueue_->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);
    D3D12_MESSAGE_ID denyIds[] = {
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE};
    D3D12_MESSAGE_SEVERITY severities[] = {D3D12_MESSAGE_SEVERITY_INFO};
    D3D12_INFO_QUEUE_FILTER filter{};
    filter.DenyList.NumIDs = _countof(denyIds);
    filter.DenyList.pIDList = denyIds;
    filter.DenyList.NumSeverities = _countof(severities);
    filter.DenyList.pSeverityList = severities;
    infoQueue_->PushStorageFilter(&filter);
  }

  NotifyObserversCreateComp();
}
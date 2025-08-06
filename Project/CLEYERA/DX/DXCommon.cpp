#include "DXCommon.h"
#include "DXManager.h"

using namespace CLEYERA::Base::DX;

/// フェンス生成

/// <summary>
///
/// </summary>
void DXCommon::Create() {

   dxManager_ = DXManager::GetInstance();

#ifdef _DEBUG
   debugLayer_ = std::make_shared<DXDebugLayer>(VAR_NAME(DXDebugLayer));
   componentList_.push_back(debugLayer_);
#endif // _DEBUG

   factory_ = std::make_shared<DXFactory>(VAR_NAME(DXFactory));
   componentList_.push_back(factory_);
   adapter_ = std::make_shared<DXAdapter>(VAR_NAME(DXAdapter));
   componentList_.push_back(adapter_);
   device_ = std::make_shared<DXDevice>(VAR_NAME(DXDevice));
   componentList_.push_back(device_);

#ifdef _DEBUG
   infoQueue_ = std::make_shared<DXInfoQueue>(VAR_NAME(DXInfoQueue));
   componentList_.push_back(infoQueue_);
#endif // _DEBUG

#pragma region コマンド

   commandQueue_ = std::make_shared<DXCommandQueue>(VAR_NAME(DXCommandQueue));
   componentList_.push_back(commandQueue_);

   commandAllcator_ = std::make_shared<DXCommandAllocator>(VAR_NAME(DXCommandAllocator));
   componentList_.push_back(commandAllcator_);

   commandList_ = std::make_shared<DXCommandList>(VAR_NAME(DXCommandList));
   componentList_.push_back(commandList_);

#pragma endregion

   swapChain_ = std::make_shared<DXSwapChain>(VAR_NAME(DXSwapChain));
   componentList_.push_back(swapChain_);

#pragma region Descripter

   rtvDescripter_ = std::make_shared<DXRTVDescripter>(VAR_NAME(DXRTVDescripter));
   componentList_.push_back(rtvDescripter_);

   srvDescripter_ = std::make_shared<DXSRVDescripter>(VAR_NAME(DXSRVDescripter));
   componentList_.push_back(srvDescripter_);

   dsvDescripter_ = std::make_shared<DXDSVDescripter>(VAR_NAME(DXDSVDescripter));
   componentList_.push_back(dsvDescripter_);

#pragma endregion

   fence_ = std::make_shared<DXFence>(VAR_NAME(DXFence));
   componentList_.push_back(fence_);

   depth_ = std::make_shared<DXDepth>();

   for (auto &obj : componentList_) {
      obj.lock()->AddObserver(logManager_);
   }

#ifdef _DEBUG

   debugLayer_->Create();
   dxManager_->SetDebugLayer(debugLayer_);

#endif // _DEBUG

   factory_->Create();
   dxManager_->SetFactory(factory_);

   adapter_->Create();
   dxManager_->SetAdapter(adapter_);

   device_->Create();
   dxManager_->SetDevice(device_);

#ifdef _DEBUG

   infoQueue_->Create();
   dxManager_->SetInfoQueue(infoQueue_);

#endif // _DEBUG

   commandQueue_->Create();
   dxManager_->SetCommandQueue(commandQueue_);

   commandAllcator_->Create();
   dxManager_->SetCommandAllocator(commandAllcator_);

   commandList_->Create();
   dxManager_->SetCommandList(commandList_);

   DXCommandManager::GetInstace()->SetCommandList(commandList_->GetCommandList());
   DXCommandManager::GetInstace()->SetCommandQueue(commandQueue_->GetCommandQueue());
   DXCommandManager::GetInstace()->SetCommandAllocator(commandAllcator_->GetCommandAllocator());

   DXCommandManager::GetInstace()->Init();

   /// descripterを作る
   rtvDescripter_->CreateDescripter(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, false);
   srvDescripter_->CreateDescripter(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, true);
   dsvDescripter_->CreateDescripter(D3D12_DESCRIPTOR_HEAP_TYPE_DSV, false);

   DXDescripterManager::GetInstance()->SetRTVDescripter(rtvDescripter_);
   DXDescripterManager::GetInstance()->SetDSVDescripter(dsvDescripter_);
   DXDescripterManager::GetInstance()->SetSRVDescripter(srvDescripter_);

   rtvDescripter_->Create();
   dxManager_->SetRTVDescripter(rtvDescripter_);

   srvDescripter_->Create();
   dsvDescripter_->Create();

   swapChain_->Create();
   dxManager_->SetSwapChain(swapChain_);

   swapChain_->RegisterRTV();

   fence_->Create();

   depth_->Init();
   dxManager_->SetDepth(depth_);

   barriers_.resize(1);
   barriers_[0] = std::make_unique<DXBarrier>();
   barriers_[0]->Init();


}

void CLEYERA::Base::DX::DXCommon::Finalize() {

   depth_.reset();

   fence_.reset();

   swapChain_.reset();

   dsvDescripter_.reset();
   srvDescripter_.reset();
   rtvDescripter_.reset();

   commandList_.reset();
   commandAllcator_.reset();
   commandQueue_.reset();
#ifdef _DEBUG
   infoQueue_.reset();
#endif // _DEBUG

   device_.reset();
   adapter_.reset();
   factory_.reset();

#ifdef _DEBUG
   debugLayer_.reset();
#endif // _DEBUG

   /// リーク
   ComPtr<IDXGIDebug1> debug;
   if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug)))) {
      debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
      debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
      debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
   }
}

void CLEYERA::Base::DX::DXCommon::PreDraw() {

   backBufferIndex_ = swapChain_->GetSwapChain()->GetCurrentBackBufferIndex();

   barriers_[0]->SetBarrierType(0, D3D12_RESOURCE_BARRIER_TYPE_TRANSITION);
   barriers_[0]->SetBarrierFlag(0, D3D12_RESOURCE_BARRIER_FLAG_NONE);
   barriers_[0]->SetBarrierState(0, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
   barriers_[0]->SetBuffer(swapChain_->GetSwapChainResource(backBufferIndex_));
   barriers_[0]->Barrier();

   std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> handles = {rtvDescripter_->GetCPUHandle(backBufferIndex_)};

   D3D12_CPU_DESCRIPTOR_HANDLE depth = dsvDescripter_->GetCPUHandle(depth_->GetBuf()->GetDSVIndex());

   DXCommandManager::GetInstace()->OMRenderTargets(handles, &depth);
   DXCommandManager::GetInstace()->ClearDepthStencilView(depth, D3D12_CLEAR_FLAG_DEPTH);

   swapChain_->Begin();
}

void CLEYERA::Base::DX::DXCommon::PostDraw() {
   ID3D12CommandList *list[] = {commandList_->GetCommandList()};
   ID3D12GraphicsCommandList *commandList = commandList_->GetCommandList();
   ID3D12CommandQueue *queue = commandQueue_->GetCommandQueue();

   IDXGISwapChain4 *swapChain = swapChain_->GetSwapChain();

   barriers_[0]->SetBarrierState(0, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
   barriers_[0]->Barrier();

 [[maybe_unused]] HRESULT hr = commandList->Close();
   assert(SUCCEEDED(hr));

   queue->ExecuteCommandLists(1, list);
   swapChain->Present(1, 0);

   fence_->End();

 
}

void CLEYERA::Base::DX::DXCommon::ImGuiUpdate() { }

void CLEYERA::Base::DX::DXCommon::CommandReset() {
   ID3D12GraphicsCommandList *commandList = commandList_->GetCommandList();
   ID3D12CommandAllocator *allocator = commandAllcator_->GetCommandAllocator();

   HRESULT hr = allocator->Reset();
   assert(SUCCEEDED(hr));

   hr = commandList->Reset(allocator, nullptr);
   assert(SUCCEEDED(hr));
}

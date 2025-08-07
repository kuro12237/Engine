#include "DXSwapChain.h"
#include "../DXManager.h"

void CLEYERA::Base::DX::DXSwapChain::Create() {

   dxManager_ = DXManager::GetInstance();
   descripterManager_ = DXDescripterManager::GetInstance();
   commandManager_ = DX::DXCommandManager::GetInstace();

   IDXGIFactory7 *factory = dxManager_->GetFactory();
   ID3D12CommandQueue *queue = dxManager_->GetCommandQueue();

   winApp_ = Win::WinApp::GetInstance();

   HWND hwnd = winApp_->GetHWND();

   swapChainDesc_.Width = winApp_->GetKWindowWidth();
   swapChainDesc_.Height = winApp_->GetKWindowHeight();
   swapChainDesc_.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
   swapChainDesc_.SampleDesc.Count = 1;
   swapChainDesc_.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
   swapChainDesc_.BufferCount = static_cast<UINT>(swapChainCount_);
   swapChainDesc_.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

   factory->CreateSwapChainForHwnd(queue, hwnd, &swapChainDesc_, nullptr, nullptr, reinterpret_cast<IDXGISwapChain1 **>(swapChain_.GetAddressOf()));

   CreateResources();

   NotifyObserversCreateComp();
}

void CLEYERA::Base::DX::DXSwapChain::RegisterRTV() {

   rtvDesc_.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
   rtvDesc_.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

   /// ハンドルのぽいんたげっと
   for (size_t i = 0; i < this->swapChainCount_; i++) {
      resources_[i]->RegisterRTV(rtvDesc_);
   }
}

void CLEYERA::Base::DX::DXSwapChain::Begin() { backBufferIndex_ = swapChain_->GetCurrentBackBufferIndex(); }

void CLEYERA::Base::DX::DXSwapChain::SwapChainResourceState(const D3D12_RESOURCE_BARRIER &barrier) { this->commandManager_->Barrier(barrier); }

void CLEYERA::Base::DX::DXSwapChain::RTVCopyBuf(ID3D12Resource *buf) { commandManager_->CopyResource(resources_[backBufferIndex_]->GetResource(), buf); }

void CLEYERA::Base::DX::DXSwapChain::CreateResources() {

   for (size_t i = 0; i < this->swapChainCount_; i++) {
      ComPtr<ID3D12Resource> resource = nullptr;
      resources_[i] = std::make_unique<DXBufferResource<uint32_t>>();
      resources_[i]->Init();
      [[maybe_unused]] HRESULT hr =
          swapChain_->GetBuffer(static_cast<UINT>(i), IID_PPV_ARGS(&resource));
      D3D12_RENDER_TARGET_VIEW_DESC desc;

      desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
      desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
      resources_[i]->SetResource(resource);

      assert(SUCCEEDED(hr));
   }
}

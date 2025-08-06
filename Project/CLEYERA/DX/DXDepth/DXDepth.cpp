#include "DXDepth.h"
#include "../../WIn/WinApp.h"
#include "../DXManager.h"

void CLEYERA::Base::DX::DXDepth::Init() {

   winApp_ = Win::WinApp::GetInstance();

   D3D12_RESOURCE_DESC desc{};
   desc.Width = winApp_->GetKWindowWidth();
   desc.Height = winApp_->GetKWindowHeight();
   desc.MipLevels = 1;
   desc.DepthOrArraySize = 1;
   desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
   desc.SampleDesc.Count = 1;
   desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
   desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

   D3D12_HEAP_PROPERTIES heap{};
   heap.Type = D3D12_HEAP_TYPE_DEFAULT;

   D3D12_CLEAR_VALUE depthClearValue{};
   depthClearValue.DepthStencil.Depth = 1.0f;
   depthClearValue.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

   buf_ = std::make_unique<DXBufferResource<int32_t>>();
   buf_->Init();
   buf_->SetDevice(DXManager::GetInstance()->GetDevice());

   buf_->CreateBuffer(heap, D3D12_HEAP_FLAG_NONE, desc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &depthClearValue);

   D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
   dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
   dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;

   buf_->RegisterDSV(dsvDesc);
}
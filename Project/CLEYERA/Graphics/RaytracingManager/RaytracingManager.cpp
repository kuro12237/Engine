#include "RaytracingManager.h"

void CLEYERA::Graphics::RaytracingManager::Create() {
   dxManager_ = CLEYERA::Base::DX::DXManager::GetInstance();
   commandManager_ = CLEYERA::Base::DX::DXCommandManager::GetInstace();
   descripterManager_ = CLEYERA::Base::DX::DXDescripterManager::GetInstance();

   CreateOutPutUAV();

   barrier_.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
   barrier_.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
   barrier_.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
}

void CLEYERA::Graphics::RaytracingManager::PreRaytracing() {
   barrier_.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
   barrier_.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
   barrier_.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
   commandManager_->Barrier(barrier_);



}

void CLEYERA::Graphics::RaytracingManager::PostRaytracing() {

   barrier_.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
   barrier_.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
   barrier_.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
   commandManager_->Barrier(barrier_);
}

void CLEYERA::Graphics::RaytracingManager::DispachRay() {
   auto gpuHandle = descripterManager_->GetSRVGPUHandle(outputBuf_->GetSRVIndex());
   commandManager_->ComputeDescripterTable(4, gpuHandle);


   commandManager_->DispachRay(*dispachRayDesc_);

}

void CLEYERA::Graphics::RaytracingManager::CreateOutPutUAV() {

   outputBuf_ = std::make_unique<Base::DX::DXBufferResource<int32_t>>();

   outputBuf_->SetDevice(dxManager_->GetDevice());
   Math::Vector::Vec2 size = {float(Base::Win::WinApp::GetKWindowWidth()), float(Base::Win::WinApp::GetKWindowHeight())};

   outputBuf_->Init(static_cast<size_t>(size.x * size.y));

   outputBuf_->CreateTexture2d(size, DXGI_FORMAT_R8G8B8A8_UNORM, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_COPY_SOURCE, D3D12_HEAP_TYPE_DEFAULT);

   D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc{};
   uavDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
   outputBuf_->RegisterUAV(uavDesc);
}

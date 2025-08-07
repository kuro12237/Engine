#include "DXRTVDescripter.h"
#include "../DXManager.h"

void CLEYERA::Base::DX::DXRTVDescripter::Create() {

   dxManager_ = DXManager::GetInstance();
   device_ = dxManager_->GetDevice();

   gpuHandles_.resize(this->descripterSize_);
   cpuHandles_.resize(this->descripterSize_);

   NotifyObserversCreateComp();
}

size_t CLEYERA::Base::DX::DXRTVDescripter::AddPtr(ID3D12Resource *buf, D3D12_RENDER_TARGET_VIEW_DESC desc) {

   size_t newHandle;

   ///再利用するか
   if (!indexFreeList_.empty()) {
      newHandle = indexFreeList_.back();
      indexFreeList_.pop_back();
   } else {
      newHandle = handleIndex_;
      handleIndex_++;
   }

   //ずらして作成
   uint32_t size = device_->GetDescriptorHandleIncrementSize(type_);
   D3D12_CPU_DESCRIPTOR_HANDLE start = descripter_->GetCPUDescriptorHandleForHeapStart();

   cpuHandles_[newHandle].ptr = start.ptr + size * newHandle;

   device_->CreateRenderTargetView(buf, &desc, cpuHandles_[newHandle]);

   return newHandle;
}

#include "DXSRVDescripter.h"
#include "../DXManager.h"

void CLEYERA::Base::DX::DXSRVDescripter::Create() {
   dxManager_ = DXManager::GetInstance();
   device_ = dxManager_->GetDevice();

   gpuHandles_.resize(this->descripterSize_);
   cpuHandles_.resize(this->descripterSize_);

   NotifyObserversCreateComp();
}

size_t CLEYERA::Base::DX::DXSRVDescripter::AddSRVPtr() {

   size_t newHandle;

   /// 再利用するか
   if (!indexFreeList_.empty()) {
      newHandle = indexFreeList_.back();
      indexFreeList_.pop_back();
   } else {
      newHandle = handleIndex_;
   }

   // ずらして作成

   uint32_t size = device_->GetDescriptorHandleIncrementSize(type_);

   D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descripter_->GetCPUDescriptorHandleForHeapStart();
   D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descripter_->GetGPUDescriptorHandleForHeapStart();

   cpuHandles_[newHandle].ptr = handleCPU.ptr + size * newHandle;
   gpuHandles_[newHandle].ptr = handleGPU.ptr + size * newHandle;

   handleIndex_++;

   return newHandle;
}

size_t CLEYERA::Base::DX::DXSRVDescripter::AddUAVPtr(ID3D12Resource *buf, D3D12_UNORDERED_ACCESS_VIEW_DESC desc) {

   size_t newHandle;

   /// 再利用するか
   if (!indexFreeList_.empty()) {
      newHandle = indexFreeList_.back();
      indexFreeList_.pop_back();
   } else {
      newHandle = handleIndex_;
   }

   // ずらして作成

   uint32_t size = device_->GetDescriptorHandleIncrementSize(type_);

   D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descripter_->GetCPUDescriptorHandleForHeapStart();
   D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descripter_->GetGPUDescriptorHandleForHeapStart();

   cpuHandles_[newHandle].ptr = handleCPU.ptr + size * newHandle;
   gpuHandles_[newHandle].ptr = handleGPU.ptr + size * newHandle;

   device_->CreateUnorderedAccessView(buf, nullptr, &desc, cpuHandles_[newHandle]);
   handleIndex_++;
   return newHandle;
}

size_t CLEYERA::Base::DX::DXSRVDescripter::AddSRVCreatePtr(ID3D12Resource *buf, D3D12_SHADER_RESOURCE_VIEW_DESC desc) {

   size_t newHandle = handleIndex_;

   // 再利用するか
   if (!indexFreeList_.empty()) {
      newHandle = indexFreeList_.back();
      indexFreeList_.pop_back();
   } else {
      newHandle = handleIndex_;
      handleIndex_++;
   }

   // ずらして作成

   uint32_t size = device_->GetDescriptorHandleIncrementSize(type_);

   D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descripter_->GetCPUDescriptorHandleForHeapStart();
   D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descripter_->GetGPUDescriptorHandleForHeapStart();

   cpuHandles_[newHandle].ptr = handleCPU.ptr + size * newHandle;
   gpuHandles_[newHandle].ptr = handleGPU.ptr + size * newHandle;

   if (desc.ViewDimension == D3D12_SRV_DIMENSION_RAYTRACING_ACCELERATION_STRUCTURE) {
      device_->CreateShaderResourceView(nullptr, &desc, cpuHandles_[newHandle]);
   } else {
      device_->CreateShaderResourceView(buf, &desc, cpuHandles_[newHandle]);
   }

   return newHandle;
}

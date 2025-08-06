#include "DXDescripterComponent.h"
#include "../DXManager.h"

void CLEYERA::Base::DX::DXDescripterComponent::CreateDescripter(
    const D3D12_DESCRIPTOR_HEAP_TYPE &type, bool shaderVisible) {

  type_ = type;
  dxManager_ = DXManager::GetInstance();
  ID3D12Device *device = dxManager_->GetDevice();

  D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc{};
  descriptorHeapDesc.Type = type;
  descriptorHeapDesc.NumDescriptors = static_cast<UINT>(descripterSize_);

  descriptorHeapDesc.Flags = shaderVisible
                                 ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE
                                 : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

  [[maybe_unused]] HRESULT hr =
      device->CreateDescriptorHeap(&descriptorHeapDesc,
                                            IID_PPV_ARGS(&descripter_));
  assert(SUCCEEDED(hr));
}
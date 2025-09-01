#include "ClosestHitRootSignature.h"

void CLEYERA::Model3d::system::CloseHitRootSignature::Create() {

   ID3D12Device5 *device = Base::DX::DXManager::GetInstance()->GetDevice();

   D3D12_DESCRIPTOR_RANGE rangeIB{};
   rangeIB.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
   rangeIB.BaseShaderRegister = 0;
   rangeIB.NumDescriptors = 1;
   rangeIB.RegisterSpace = 1;
   rangeIB.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

   D3D12_DESCRIPTOR_RANGE rangeVB{};
   rangeVB.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
   rangeVB.BaseShaderRegister = 1;
   rangeVB.NumDescriptors = 1;
   rangeVB.RegisterSpace = 1;
   rangeVB.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

   std::array<D3D12_ROOT_PARAMETER, 2> rootParams;
   rootParams[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
   rootParams[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
   rootParams[0].DescriptorTable.NumDescriptorRanges = 1;
   rootParams[0].DescriptorTable.pDescriptorRanges = &rangeIB;

   rootParams[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
   rootParams[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
   rootParams[1].DescriptorTable.NumDescriptorRanges = 1;
   rootParams[1].DescriptorTable.pDescriptorRanges = &rangeVB;

   D3D12_ROOT_SIGNATURE_DESC rootSigDesc{};
   rootSigDesc.NumParameters = UINT(rootParams.size());
   rootSigDesc.pParameters = rootParams.data();
   rootSigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_LOCAL_ROOT_SIGNATURE;

   ComPtr<ID3DBlob> blob, errBlob;
   HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &blob, &errBlob);
   assert(SUCCEEDED(hr));

   hr = device->CreateRootSignature(0, blob->GetBufferPointer(), blob->GetBufferSize(), IID_PPV_ARGS(rootSignature_.ReleaseAndGetAddressOf()));
   assert(SUCCEEDED(hr));
}
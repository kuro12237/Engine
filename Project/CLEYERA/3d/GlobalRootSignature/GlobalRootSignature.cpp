#include "GlobalRootSignature.h"

void CLEYERA::Model3d::system::GlobalRootSignature::Init() {

   ID3D12Device5 *device = Base::DX::DXManager::GetInstance()->GetDevice();

   std::array<D3D12_ROOT_PARAMETER, 5> rootParams{};

   D3D12_DESCRIPTOR_RANGE descRangeTLAS{};
   descRangeTLAS.BaseShaderRegister = 0;
   descRangeTLAS.NumDescriptors = 1;
   descRangeTLAS.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;

   rootParams[0] = D3D12_ROOT_PARAMETER{};
   rootParams[1] = D3D12_ROOT_PARAMETER{};

   rootParams[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
   rootParams[0].DescriptorTable.NumDescriptorRanges = 1;
   rootParams[0].DescriptorTable.pDescriptorRanges = &descRangeTLAS;

   rootParams[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
   rootParams[1].Descriptor.ShaderRegister = 0;
   rootParams[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

   D3D12_DESCRIPTOR_RANGE rangeIB{};
   rangeIB.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
   rangeIB.BaseShaderRegister = 1;
   rangeIB.NumDescriptors = 1;
   rangeIB.RegisterSpace = 0;
   rangeIB.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

   D3D12_DESCRIPTOR_RANGE rangeVB{};
   rangeVB.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
   rangeVB.BaseShaderRegister = 2;
   rangeVB.NumDescriptors = 1;
   rangeVB.RegisterSpace = 0;
   rangeVB.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

   rootParams[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
   rootParams[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
   rootParams[2].DescriptorTable.NumDescriptorRanges = 1;
   rootParams[2].DescriptorTable.pDescriptorRanges = &rangeIB;

   rootParams[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
   rootParams[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
   rootParams[3].DescriptorTable.NumDescriptorRanges = 1;
   rootParams[3].DescriptorTable.pDescriptorRanges = &rangeVB;

   D3D12_DESCRIPTOR_RANGE range;

   range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
   range.BaseShaderRegister = 3;
   range.NumDescriptors = 1;
   range.RegisterSpace = 0;
   range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

   rootParams[4].DescriptorTable.NumDescriptorRanges = 1;
   rootParams[4].DescriptorTable.pDescriptorRanges = &range;
   rootParams[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
   rootParams[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;

   D3D12_ROOT_SIGNATURE_DESC rootSigDesc{};
   rootSigDesc.NumParameters = UINT(rootParams.size());
   rootSigDesc.pParameters = rootParams.data();

   HRESULT hr;
   Microsoft::WRL::ComPtr<ID3DBlob> blob, errBlob;
   hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &blob, &errBlob);
   assert(SUCCEEDED(hr));

   hr = device->CreateRootSignature(0, blob->GetBufferPointer(), blob->GetBufferSize(), IID_PPV_ARGS(rootSignature_.ReleaseAndGetAddressOf()));
   assert(SUCCEEDED(hr));
}

void CLEYERA::Model3d::system::GlobalRootSignature::Render() {

   auto list = CLEYERA::Base::DX::DXCommandManager::GetInstace()->GetCommandList();
   list->SetComputeRootSignature(rootSignature_.Get());
}

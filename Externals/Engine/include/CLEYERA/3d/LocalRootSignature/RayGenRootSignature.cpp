#include "RayGenRootSignature.h"

void CLEYERA::Model3d::system::RayGenRootSignature::Create() {

   ID3D12Device5 *device = Base::DX::DXManager::GetInstance()->GetDevice();

   D3D12_DESCRIPTOR_RANGE range;

   range.BaseShaderRegister = 0;
   range.NumDescriptors = 1;
   range.RegisterSpace = 1;
   range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;

   range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

   std::array<D3D12_ROOT_PARAMETER, 1> rootparam;
   rootparam[0].DescriptorTable.NumDescriptorRanges = 1;
   rootparam[0].DescriptorTable.pDescriptorRanges = &range;
   rootparam[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
   rootparam[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;

   ComPtr<ID3DBlob> blob, errBlob;
   D3D12_ROOT_SIGNATURE_DESC rootSigDesc{};
   rootSigDesc.NumParameters = UINT(rootparam.size());
   rootSigDesc.pParameters = rootparam.data();
   rootSigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_LOCAL_ROOT_SIGNATURE;

   HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &blob, &errBlob);
   assert(SUCCEEDED(hr));

   hr = device->CreateRootSignature(0, blob->GetBufferPointer(), blob->GetBufferSize(), IID_PPV_ARGS(rootSignature_.ReleaseAndGetAddressOf()));
   assert(SUCCEEDED(hr));
}
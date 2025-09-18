#include "DFModel3dDraw.h"

void CLEYERA::Graphics::Raster::system::DFModel3dDraw::SettingShader() {

  shaders_[Shader::ShaderMode::PS] =
      shaderManager_->GetShader(mode3d_, Shader::ShaderMode::PS);
  shaders_[Shader::ShaderMode::VS] =
      shaderManager_->GetShader(mode3d_, Shader::ShaderMode::VS);
}

void CLEYERA::Graphics::Raster::system::DFModel3dDraw::SettingRootParam() {

  this->rootParam_.resize(6);

  // かめら
  rootParam_[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
  rootParam_[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
  rootParam_[0].Descriptor.ShaderRegister = 0;

  worldDescriptor[0].BaseShaderRegister = 1;
  worldDescriptor[0].NumDescriptors = 1;
  worldDescriptor[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
  worldDescriptor[0].OffsetInDescriptorsFromTableStart =
      D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

  // world
  rootParam_[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  rootParam_[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
  rootParam_[1].DescriptorTable.pDescriptorRanges = worldDescriptor;
  rootParam_[1].DescriptorTable.NumDescriptorRanges = _countof(worldDescriptor);

  // texDescriptorRanged
  descriptorRangeVertices[0].BaseShaderRegister = 0;
  descriptorRangeVertices[0].NumDescriptors = 1;
  descriptorRangeVertices[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
  descriptorRangeVertices[0].OffsetInDescriptorsFromTableStart =
      D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

  // tex
  rootParam_[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  rootParam_[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
  rootParam_[2].DescriptorTable.pDescriptorRanges = descriptorRangeVertices;
  rootParam_[2].DescriptorTable.NumDescriptorRanges =
      _countof(descriptorRangeVertices);

  // light
  rootParam_[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
  rootParam_[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
  rootParam_[3].Descriptor.ShaderRegister = 0;

  rootParam_[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
  rootParam_[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
  rootParam_[4].Descriptor.ShaderRegister = 2;

  materialDescriptor[0].BaseShaderRegister = 3;
  materialDescriptor[0].NumDescriptors = 1;
  materialDescriptor[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
  materialDescriptor[0].OffsetInDescriptorsFromTableStart =
      D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

  // world
  rootParam_[5].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  rootParam_[5].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
  rootParam_[5].DescriptorTable.pDescriptorRanges = materialDescriptor;
  rootParam_[5].DescriptorTable.NumDescriptorRanges =
      _countof(materialDescriptor);
}

void CLEYERA::Graphics::Raster::system::DFModel3dDraw::SettingSampler() {

  // Sampler
  this->staticSamplers_.resize(1);

  staticSamplers_[0].Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
  staticSamplers_[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
  staticSamplers_[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
  staticSamplers_[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;

  staticSamplers_[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
  staticSamplers_[0].MaxLOD = D3D12_FLOAT32_MAX;
  staticSamplers_[0].ShaderRegister = 0;
  staticSamplers_[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
}

void CLEYERA::Graphics::Raster::system::DFModel3dDraw::SettingInput() {

  // Output
  inputElementDesc_.resize(4);
  inputElementDesc_[0].SemanticName = "POSITION";
  inputElementDesc_[0].SemanticIndex = 0;
  inputElementDesc_[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
  inputElementDesc_[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;


  inputElementDesc_[2].SemanticName = "TEXCOORD";
  inputElementDesc_[2].SemanticIndex = 0;
  inputElementDesc_[2].Format = DXGI_FORMAT_R32G32_FLOAT;
  inputElementDesc_[2].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

  inputElementDesc_[1].SemanticName = "NORMAL";
  inputElementDesc_[1].SemanticIndex = 0;
  inputElementDesc_[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
  inputElementDesc_[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

  inputElementDesc_[3].SemanticName = "INSTANCEID";
  inputElementDesc_[3].SemanticIndex = 0;
  inputElementDesc_[3].Format = DXGI_FORMAT_R8_UINT;
  inputElementDesc_[3].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

  inputLayoutDesc.pInputElementDescs = inputElementDesc_.data();
  inputLayoutDesc.NumElements = UINT(inputElementDesc_.size());
}

void CLEYERA::Graphics::Raster::system::DFModel3dDraw::SettingDepth() {
  despthStencilDesc_ = {};
  despthStencilDesc_.DepthEnable = true;
  despthStencilDesc_.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
  despthStencilDesc_.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
}

void CLEYERA::Graphics::Raster::system::DFModel3dDraw::RtvSetting() {
  rtvFormats_.resize(2);
  rtvFormats_[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
  rtvFormats_[1] = DXGI_FORMAT_R8G8B8A8_UNORM;
}

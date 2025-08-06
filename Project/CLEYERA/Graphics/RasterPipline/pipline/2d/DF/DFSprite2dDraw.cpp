#include "DFSprite2dDraw.h"

void CLEYERA::Graphics::Raster::system::DFSprite2dDraw::SettingShader() {
  shaders_[Shader::ShaderMode::PS] = shaderManager_->GetShader(mode2d_, Shader::ShaderMode::PS);
  shaders_[Shader::ShaderMode::VS] = shaderManager_->GetShader(mode2d_, Shader::ShaderMode::VS);
}

void CLEYERA::Graphics::Raster::system::DFSprite2dDraw::SettingRootParam() {
  this->rootParam_.resize(4);

  // かめら
  rootParam_[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
  rootParam_[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
  rootParam_[0].Descriptor.ShaderRegister = 0;
  // world
  rootParam_[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
  rootParam_[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
  rootParam_[1].Descriptor.ShaderRegister = 1;

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
  rootParam_[2].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeVertices);
  // mat
  rootParam_[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
  rootParam_[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
  rootParam_[3].Descriptor.ShaderRegister = 2;
}

void CLEYERA::Graphics::Raster::system::DFSprite2dDraw::SettingSampler() {

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

void CLEYERA::Graphics::Raster::system::DFSprite2dDraw::SettingInput() {

       // Output
  inputElementDesc_.resize(2);
  inputElementDesc_[0].SemanticName = "POSITION";
  inputElementDesc_[0].SemanticIndex = 0;
  inputElementDesc_[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
  inputElementDesc_[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

  inputElementDesc_[1].SemanticName = "TEXCOORD";
  inputElementDesc_[1].SemanticIndex = 0;
  inputElementDesc_[1].Format = DXGI_FORMAT_R32G32_FLOAT;
  inputElementDesc_[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

  inputLayoutDesc.pInputElementDescs = inputElementDesc_.data();
  inputLayoutDesc.NumElements = UINT(inputElementDesc_.size());
}

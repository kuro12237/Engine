#include "PostEffectCopy.h"

void CLEYERA::Graphics::Raster::system::PostEffectCopy::SettingShader() {

  shaders_[Shader::ShaderMode::PS] =
      shaderManager_->GetShader(this->postEffectMode_, Shader::ShaderMode::PS);
  shaders_[Shader::ShaderMode::VS] =
      shaderManager_->GetShader(this->postEffectMode_, Shader::ShaderMode::VS);
}

void CLEYERA::Graphics::Raster::system::PostEffectCopy::SettingRootParam() {

 this->rootParam_.resize(7);

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
  rootParam_[2].DescriptorTable.NumDescriptorRanges =
      _countof(descriptorRangeVertices);

  // normal
  descriptorRangeNormal[0].BaseShaderRegister = 1;
  descriptorRangeNormal[0].NumDescriptors = 1;
  descriptorRangeNormal[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
  descriptorRangeNormal[0].OffsetInDescriptorsFromTableStart =
      D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
  // tex
  rootParam_[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  rootParam_[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
  rootParam_[3].DescriptorTable.pDescriptorRanges = descriptorRangeNormal;
  rootParam_[3].DescriptorTable.NumDescriptorRanges =
      _countof(descriptorRangeNormal);

  // Depth
  descriptorRangeDepth[0].BaseShaderRegister = 2;
  descriptorRangeDepth[0].NumDescriptors = 1;
  descriptorRangeDepth[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
  descriptorRangeDepth[0].OffsetInDescriptorsFromTableStart =
      D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
  // tex
  rootParam_[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  rootParam_[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
  rootParam_[4].DescriptorTable.pDescriptorRanges = descriptorRangeDepth;
  rootParam_[4].DescriptorTable.NumDescriptorRanges =
      _countof(descriptorRangeDepth);

   // かめら
  rootParam_[5].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
  rootParam_[5].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
  rootParam_[5].Descriptor.ShaderRegister = 0;

  // ライトdirection
  rootParam_[6].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
  rootParam_[6].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
  rootParam_[6].Descriptor.ShaderRegister = 1;
}

void CLEYERA::Graphics::Raster::system::PostEffectCopy::SettingSampler() {

  // Sampler
  this->staticSamplers_.resize(2);

  staticSamplers_[0].Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
  staticSamplers_[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
  staticSamplers_[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
  staticSamplers_[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;

  staticSamplers_[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
  staticSamplers_[0].MaxLOD = D3D12_FLOAT32_MAX;
  staticSamplers_[0].ShaderRegister = 0;
  staticSamplers_[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

  staticSamplers_[1].Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
  staticSamplers_[1].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
  staticSamplers_[1].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
  staticSamplers_[1].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
  staticSamplers_[1].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
  staticSamplers_[1].MaxLOD = D3D12_FLOAT32_MAX;
  staticSamplers_[1].ShaderRegister = 1;
  staticSamplers_[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
}

void CLEYERA::Graphics::Raster::system::PostEffectCopy::SettingInput() {
  // Output
  inputElementDesc_.resize(4);
  inputElementDesc_[0].SemanticName = "POSITION";
  inputElementDesc_[0].SemanticIndex = 0;
  inputElementDesc_[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
  inputElementDesc_[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

  inputElementDesc_[1].SemanticName = "NORMAL";
  inputElementDesc_[1].SemanticIndex = 0;
  inputElementDesc_[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
  inputElementDesc_[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

  inputElementDesc_[2].SemanticName = "TEXCOORD";
  inputElementDesc_[2].SemanticIndex = 0;
  inputElementDesc_[2].Format = DXGI_FORMAT_R32G32_FLOAT;
  inputElementDesc_[2].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

  inputElementDesc_[3].SemanticName = "INSTANCEID";
  inputElementDesc_[3].SemanticIndex = 0;
  inputElementDesc_[3].Format = DXGI_FORMAT_R8_UINT;
  inputElementDesc_[3].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

  inputLayoutDesc.pInputElementDescs = inputElementDesc_.data();
  inputLayoutDesc.NumElements = UINT(inputElementDesc_.size());
}

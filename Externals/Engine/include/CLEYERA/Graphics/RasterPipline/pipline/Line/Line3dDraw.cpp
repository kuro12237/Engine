#include "Line3dDraw.h"

void CLEYERA::Graphics::Raster::system::Line3dDraw::SettingShader() {

   shaders_[Shader::ShaderMode::PS] = shaderManager_->GetShader(mode3d_, Shader::ShaderMode::PS);
   shaders_[Shader::ShaderMode::VS] = shaderManager_->GetShader(mode3d_, Shader::ShaderMode::VS);
}

void CLEYERA::Graphics::Raster::system::Line3dDraw::SettingRootParam() {
   this->rootParam_.resize(4);

   // かめら
   rootParam_[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
   rootParam_[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
   rootParam_[0].Descriptor.ShaderRegister = 0;
   // world
   rootParam_[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
   rootParam_[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
   rootParam_[1].Descriptor.ShaderRegister = 1;
   // Line
   descriptorRangeVertices[0].BaseShaderRegister = 0;
   descriptorRangeVertices[0].NumDescriptors = 1;
   descriptorRangeVertices[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
   descriptorRangeVertices[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
   descriptorRangeVertices[0].RegisterSpace = 0;

   rootParam_[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
   rootParam_[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
   rootParam_[2].DescriptorTable.pDescriptorRanges = descriptorRangeVertices;
   rootParam_[2].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeVertices);
   // LineColor

   descriptorRangeColors[0].BaseShaderRegister = 0;
   descriptorRangeColors[0].NumDescriptors = 1;
   descriptorRangeColors[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
   descriptorRangeColors[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
   descriptorRangeColors[0].RegisterSpace = 0;

   rootParam_[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
   rootParam_[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
   rootParam_[3].DescriptorTable.pDescriptorRanges = descriptorRangeColors;
   rootParam_[3].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeColors);
}

void CLEYERA::Graphics::Raster::system::Line3dDraw::SettingSampler() {}

void CLEYERA::Graphics::Raster::system::Line3dDraw::SettingInput() {

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

   primitiveType_ = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
}

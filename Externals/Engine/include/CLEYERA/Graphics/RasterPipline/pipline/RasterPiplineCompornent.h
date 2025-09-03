#pragma once
#include "../../../DX/DXManager.h"
#include "../../../pch/Pch.h"
#include "../../ShaderManager/ShaderManager.h"

namespace CLEYERA {

namespace Graphics {

namespace Raster {

namespace system {

class RasterPiplineCompornent {
 public:
   RasterPiplineCompornent() {};
   virtual ~RasterPiplineCompornent() {};

   void Init();

   void Create();

   void SetMode(RasterPipline_Mode3d mode) { mode3d_ = mode; }
   void SetMode(RasterPipline_Mode2d mode) { mode2d_ = mode; }

#pragma region Get
   ID3D12PipelineState *GetPipline() { return GraphicsPipelineState_.Get(); }
   ID3D12RootSignature *GetRootSignature() { return rootSignature_.Get(); }

#pragma endregion

 private:
   void CreateRootSignature();
   void CreatePipline();

   ID3D12Device5 *device_ = nullptr;

 protected:
#pragma region Set
   void SetFilePath(Shader::ShaderMode mode, std::string file) { filePath_[mode] = file; }

#pragma endregion

   virtual void SettingShader() = 0;
   virtual void SettingRootParam() = 0;
   virtual void SettingSampler() = 0;
   virtual void SettingInput() = 0;
   virtual void SettingRaster();
   virtual void SettingDepth();
   virtual void SettingPipline();
   virtual void SettingBlend();

   Shader::ShaderManager *shaderManager_ = nullptr;
   RasterPipline_Mode3d mode3d_;
   RasterPipline_Mode2d mode2d_;

   D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature_{};
   std::vector<D3D12_ROOT_PARAMETER> rootParam_;
   std::vector<D3D12_DESCRIPTOR_RANGE> ganges_;
   std::vector<D3D12_STATIC_SAMPLER_DESC> staticSamplers_;
   std::vector<D3D12_INPUT_ELEMENT_DESC> inputElementDesc_;
   D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};

   D3D12_RASTERIZER_DESC rasterizerDesc_{};
   D3D12_BLEND_DESC blendDesc_{};
   D3D12_DEPTH_STENCIL_DESC despthStencilDesc_;
   D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineStateDesc_{};
   D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveType_ = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

   DXGI_FORMAT depthFormat_ = DXGI_FORMAT_D24_UNORM_S8_UINT;

   ComPtr<ID3D12PipelineState> GraphicsPipelineState_ = nullptr;
   ComPtr<ID3D12RootSignature> rootSignature_ = nullptr;

   std::map<Shader::ShaderMode, std::string> filePath_;
   std::map<Shader::ShaderMode, IDxcBlob *> shaders_;
};

} // namespace system
} // namespace Raster
} // namespace Graphics
} // namespace CLEYERA
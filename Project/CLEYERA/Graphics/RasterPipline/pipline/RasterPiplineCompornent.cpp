#include "RasterPiplineCompornent.h"

void CLEYERA::Graphics::Raster::system::RasterPiplineCompornent::Init() {

   shaderManager_ = Shader::ShaderManager::GetInstance();
   device_ = Base::DX::DXManager::GetInstance()->GetDevice();
}

void CLEYERA::Graphics::Raster::system::RasterPiplineCompornent::Create() {

   SettingShader();
   SettingRootParam();
   SettingSampler();
   this->CreateRootSignature();

   SettingInput();
   SettingBlend();
   SettingRaster();
   SettingDepth();
   SettingPipline();

   this->CreatePipline();
}

void CLEYERA::Graphics::Raster::system::RasterPiplineCompornent::CreateRootSignature() {
   descriptionRootSignature_.pStaticSamplers = staticSamplers_.data();
   descriptionRootSignature_.NumStaticSamplers = UINT(staticSamplers_.size());
   descriptionRootSignature_.pParameters = rootParam_.data();
   descriptionRootSignature_.NumParameters = UINT(rootParam_.size());
   descriptionRootSignature_.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

   ComPtr<ID3DBlob> signatureBlob = nullptr;
   ComPtr<ID3DBlob> errorBlob = nullptr;
   HRESULT hr = D3D12SerializeRootSignature(&descriptionRootSignature_, D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
   assert(SUCCEEDED(hr));

   hr = device_->CreateRootSignature(0, signatureBlob->GetBufferPointer(), signatureBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature_));
   assert(SUCCEEDED(hr));
}

void CLEYERA::Graphics::Raster::system::RasterPiplineCompornent::CreatePipline() {

 
   [[maybe_unused]] HRESULT hr = device_->CreateGraphicsPipelineState(
      &pipelineStateDesc_, IID_PPV_ARGS(&GraphicsPipelineState_));
   assert(SUCCEEDED(hr));
}

void CLEYERA::Graphics::Raster::system::RasterPiplineCompornent::SettingRaster() {

   rasterizerDesc_.CullMode = D3D12_CULL_MODE_BACK;
   rasterizerDesc_.FillMode = D3D12_FILL_MODE_SOLID;
}

void CLEYERA::Graphics::Raster::system::RasterPiplineCompornent::SettingDepth() {
   despthStencilDesc_ = {};
   despthStencilDesc_.DepthEnable = true;
   despthStencilDesc_.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
   despthStencilDesc_.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
}

void CLEYERA::Graphics::Raster::system::RasterPiplineCompornent::SettingPipline() {

   auto vs = shaders_[Shader::ShaderMode::VS];
   if (vs) {
      pipelineStateDesc_.VS = {vs->GetBufferPointer(), vs->GetBufferSize()};
   }
   auto ps = shaders_[Shader::ShaderMode::PS];
   if (ps) {
      pipelineStateDesc_.PS = {ps->GetBufferPointer(), ps->GetBufferSize()};
   }
   auto ds = shaders_[Shader::ShaderMode::DS];
   if (ds) {
      pipelineStateDesc_.DS = {ds->GetBufferPointer(), ds->GetBufferSize()};
   }
   auto hs = shaders_[Shader::ShaderMode::HS];
   if (hs) {
      pipelineStateDesc_.HS = {hs->GetBufferPointer(), hs->GetBufferSize()};
   }
   auto gs = shaders_[Shader::ShaderMode::GS];
   if (gs) {
      pipelineStateDesc_.GS = {gs->GetBufferPointer(), gs->GetBufferSize()};
   }

   pipelineStateDesc_.pRootSignature = rootSignature_.Get();
   pipelineStateDesc_.InputLayout = inputLayoutDesc;
   pipelineStateDesc_.BlendState = blendDesc_;
   pipelineStateDesc_.RasterizerState = rasterizerDesc_;
   pipelineStateDesc_.DepthStencilState = despthStencilDesc_;
   pipelineStateDesc_.DSVFormat = depthFormat_;
   pipelineStateDesc_.PrimitiveTopologyType = primitiveType_;


   pipelineStateDesc_.NumRenderTargets = 1;
   pipelineStateDesc_.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

   pipelineStateDesc_.SampleDesc.Count = 1;
   pipelineStateDesc_.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
}

void CLEYERA::Graphics::Raster::system::RasterPiplineCompornent::SettingBlend() {

   D3D12_RENDER_TARGET_BLEND_DESC &blenddesc = blendDesc_.RenderTarget[0];
   blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
   blenddesc.BlendEnable = true;

   blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
   blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
   blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;
   blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
   blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
   blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
}

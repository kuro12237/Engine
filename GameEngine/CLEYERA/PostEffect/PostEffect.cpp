#include "PostEffect.h"

using namespace CLEYERA::Base::Win;

void CLEYERA::Manager::PostEffectManager::Init() {

  auto device = Base::DX::DXManager::GetInstance()->GetDevice();

  vert_ = std::make_unique<
      Base::DX::DXBufferResource<Model3d::system::VertexForGPU>>();
  vert_->SetDevice(device);
  vert_->Init(3);
  vert_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD,
                      D3D12_RESOURCE_STATE_GENERIC_READ);
  vert_->CreateVertexBufferView();

  worldTransform_ = std::make_unique<Util::WorldTransform>();
  worldTransform_->SetScale(scale_);
  worldTransform_->SetRotate(rotate_);
  worldTransform_->SetTranslate(translate_);
  worldTransform_->WTCreate(1);
  worldTransform_->WorldMatUpdate();

  const UINT pixCount = WinApp::GetKWindowWidth() * WinApp::GetKWindowHeight();
  const UINT rowPitch = sizeof(UINT) * WinApp::GetKWindowWidth();
  const UINT depthPitch = rowPitch * WinApp::GetKWindowHeight();

  albedo_ = std::make_unique<Base::DX::DXBufferResource<uint32_t>>();
  albedo_->SetDevice(device);
  albedo_->Init(size_t(pixCount));
  DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

  albedo_->CreateTexture2d(
      {float(WinApp::GetKWindowWidth()), float(WinApp::GetKWindowHeight())},
      format, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET,
      D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_HEAP_TYPE_CUSTOM);

  albedo_->TransfarImage(pixCount, rowPitch, depthPitch);

  D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
  rtvDesc.Format = format;
  rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
  albedo_->RegisterRTV(rtvDesc);

  D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
  srvDesc.Format = format;
  srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
  srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
  srvDesc.Texture2D.MipLevels = 1;
  albedo_->RegisterSRV(srvDesc);
}

void CLEYERA::Manager::PostEffectManager::Update() {

  vertData_.resize(3);

  vertData_[0].pos = {0.0f, 0.0f, 0.0f, 1.0f};
  vertData_[1].pos = {1280.0f, 0.0f, 0.0f, 1.0f};
  vertData_[2].pos = {0.0f, 720.0f, 0.0f, 1.0f};

  vert_->SetParam(vertData_);
  vert_->Update();
}

void CLEYERA::Manager::PostEffectManager::FInalize() {

  vert_.reset();
  albedo_.reset();
  worldTransform_.reset();
}

void CLEYERA::Manager::PostEffectManager::Draw() {}

void CLEYERA::Manager::PostEffectManager::PreDraw() {

  albedo_->ChangeBufferState(D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
                             D3D12_RESOURCE_BARRIER_FLAG_NONE,
                             D3D12_RESOURCE_STATE_RENDER_TARGET);
}

void CLEYERA::Manager::PostEffectManager::PostDraw() {
  albedo_->ChangeBufferState(D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
                             D3D12_RESOURCE_BARRIER_FLAG_NONE,
                             D3D12_RESOURCE_STATE_GENERIC_READ);
}

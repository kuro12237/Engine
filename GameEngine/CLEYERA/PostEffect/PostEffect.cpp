#include "PostEffect.h"

using namespace CLEYERA::Base::Win;

void CLEYERA::Manager::PostEffectManager::Init() {

  auto device = Base::DX::DXManager::GetInstance()->GetDevice();

  vert_ = std::make_unique<Base::DX::DXBufferResource<Model3d::system::VertexForGPU>>();
  vert_->SetDevice(device);
  vert_->Init(6);
  vert_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
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

  albedo_ = CreateTexture();
  normal_ = CreateTexture();
  shadow_ = CreateTexture();

  // depth
  depth_ = std::make_unique<Base::DX::DXBufferResource<uint32_t>>();
  depth_->SetDevice(device);
  depth_->Init();
  D3D12_CLEAR_VALUE color = {};
  color.DepthStencil.Depth = 1.0f;
  color.DepthStencil.Stencil = 0.0f;
  depth_->CreateTexture2d({float(WinApp::GetKWindowWidth()), float(WinApp::GetKWindowHeight())}, DXGI_FORMAT_D24_UNORM_S8_UINT, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL, D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_HEAP_TYPE_DEFAULT, color);

  D3D12_SHADER_RESOURCE_VIEW_DESC srvDepthDesc = {};
  srvDepthDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
  srvDepthDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
  srvDepthDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
  srvDepthDesc.Texture2D.MipLevels = 1;
  depth_->RegisterSRV(srvDepthDesc);

  D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
  dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
  depth_->RegisterDSV(dsvDesc);

  vertData_.resize(6);
}

void CLEYERA::Manager::PostEffectManager::Update() {

  // 左上
  vertData_[0].pos = {0.0f, 0.0f, 0.0f, 1.0f};
  vertData_[0].texCooard = {0.0f, 0.0f};
  vertData_[0].normal.Init();
  // 右上
  vertData_[1].pos = {1280.0f, 0.0f, 0.0f, 1.0f};
  vertData_[1].texCooard = {1.0f, 0.0f};
  vertData_[1].normal.Init();
  // 左下
  vertData_[2].pos = {0.0f, 720.0f, 0.0f, 1.0f};
  vertData_[2].texCooard = {0.0f, 1.0f};
  vertData_[2].normal.Init();
  // 左下 (再利用)
  vertData_[3].pos = {0.0f, 720.0f, 0.0f, 1.0f};
  vertData_[3].texCooard = {0.0f, 1.0f};
  vertData_[3].normal.Init();
  // 右上 (再利用)
  vertData_[4].pos = {1280.0f, 0.0f, 0.0f, 1.0f};
  vertData_[4].texCooard = {1.0f, 0.0f};
  vertData_[4].normal.Init();
  // 右下
  vertData_[5].pos = {1280.0f, 720.0f, 0.0f, 1.0f};
  vertData_[5].texCooard = {1.0f, 1.0f};
  vertData_[5].normal.Init();
  vert_->Map();
  vert_->SetParam(vertData_);
  vert_->Update();
}

void CLEYERA::Manager::PostEffectManager::FInalize() {

  vert_.reset();
  normal_.reset();
  shadow_.reset();
  albedo_.reset();
  worldTransform_.reset();
  depth_.reset();
}

void CLEYERA::Manager::PostEffectManager::Draw() {}

void CLEYERA::Manager::PostEffectManager::PreDraw() {

  albedo_->ChangeBufferState(D3D12_RESOURCE_BARRIER_TYPE_TRANSITION, D3D12_RESOURCE_BARRIER_FLAG_NONE, D3D12_RESOURCE_STATE_RENDER_TARGET);
  shadow_->ChangeBufferState(D3D12_RESOURCE_BARRIER_TYPE_TRANSITION, D3D12_RESOURCE_BARRIER_FLAG_NONE, D3D12_RESOURCE_STATE_RENDER_TARGET);
  normal_->ChangeBufferState(D3D12_RESOURCE_BARRIER_TYPE_TRANSITION, D3D12_RESOURCE_BARRIER_FLAG_NONE, D3D12_RESOURCE_STATE_RENDER_TARGET);

  depth_->ChangeBufferState(D3D12_RESOURCE_BARRIER_TYPE_TRANSITION, D3D12_RESOURCE_BARRIER_FLAG_NONE, D3D12_RESOURCE_STATE_DEPTH_WRITE);

  auto command = CLEYERA::Base::DX::DXCommandManager::GetInstace();
  auto rtvDesc = CLEYERA::Base::DX::DXDescripterManager::GetInstance();

  std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> handles = {rtvDesc->GetRTVCPUHandle(albedo_->GetRTVIndex()), rtvDesc->GetRTVCPUHandle(normal_->GetRTVIndex()),rtvDesc->GetRTVCPUHandle(shadow_->GetRTVIndex())};

  D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = rtvDesc->GetDSVCPUHandle(depth_->GetDSVIndex());

  command->OMRenderTargets(handles, &dsvHandle);

  command->ClearRenderTargetView(rtvDesc->GetRTVCPUHandle(albedo_->GetRTVIndex()), {0.0f, 0.0f, 0.0f, 1.0f});
  command->ClearRenderTargetView(rtvDesc->GetRTVCPUHandle(normal_->GetRTVIndex()), {0.0f, 0.0f, 0.0f, 1.0f});
  command->ClearRenderTargetView(rtvDesc->GetRTVCPUHandle(shadow_->GetRTVIndex()), {0.0f, 0.0f, 0.0f, 1.0f});

  command->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH);
}

void CLEYERA::Manager::PostEffectManager::PostDraw() {
  albedo_->ChangeBufferState(D3D12_RESOURCE_BARRIER_TYPE_TRANSITION, D3D12_RESOURCE_BARRIER_FLAG_NONE, D3D12_RESOURCE_STATE_GENERIC_READ);
  shadow_->ChangeBufferState(D3D12_RESOURCE_BARRIER_TYPE_TRANSITION, D3D12_RESOURCE_BARRIER_FLAG_NONE, D3D12_RESOURCE_STATE_GENERIC_READ);
  normal_->ChangeBufferState(D3D12_RESOURCE_BARRIER_TYPE_TRANSITION, D3D12_RESOURCE_BARRIER_FLAG_NONE, D3D12_RESOURCE_STATE_GENERIC_READ);

  depth_->ChangeBufferState(D3D12_RESOURCE_BARRIER_TYPE_TRANSITION, D3D12_RESOURCE_BARRIER_FLAG_NONE, D3D12_RESOURCE_STATE_GENERIC_READ);
}

void CLEYERA::Manager::PostEffectManager::CommandCall(const System::PostEffectBuf &mode, uint32_t num) {
  uint32_t handle = 0;
  auto srv = Base::DX::DXDescripterManager::GetInstance()->GetSRV().lock();
  auto command = Base::DX::DXCommandManager::GetInstace();
  switch (mode) {
  case System::PostEffectBuf::Vert:
    vert_->VBCommand();

    break;

  case System::PostEffectBuf::World:
    worldTransform_->BindWT(num);

    break;

  case System::PostEffectBuf::Albedo:
    handle = albedo_->GetSRVIndex();
    command->GraphicsDescripterTable(num, srv->GetGPUHandle(handle));

    break;
  case System::PostEffectBuf::Normal:
    handle = normal_->GetSRVIndex();
    command->GraphicsDescripterTable(num, srv->GetGPUHandle(handle));

    break;
  case System::PostEffectBuf::Depth:
    handle = depth_->GetSRVIndex();
    command->GraphicsDescripterTable(num, srv->GetGPUHandle(handle));

    break;
  default:
    break;
  }
}

std::unique_ptr<CLEYERA::Base::DX::DXBufferResource<uint32_t>> CLEYERA::Manager::PostEffectManager::CreateTexture() {

  std::unique_ptr<CLEYERA::Base::DX::DXBufferResource<uint32_t>> buf_ = nullptr;
  auto device = Base::DX::DXManager::GetInstance()->GetDevice();

  const UINT pixCount = WinApp::GetKWindowWidth() * WinApp::GetKWindowHeight();
  const UINT rowPitch = sizeof(UINT) * WinApp::GetKWindowWidth();
  const UINT depthPitch = rowPitch * WinApp::GetKWindowHeight();

  buf_ = std::make_unique<Base::DX::DXBufferResource<uint32_t>>();
  buf_->SetDevice(device);
  buf_->Init(size_t(pixCount));
  DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

  buf_->CreateTexture2d({float(WinApp::GetKWindowWidth()), float(WinApp::GetKWindowHeight())}, format, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_HEAP_TYPE_CUSTOM);

  buf_->TransfarImage(pixCount, rowPitch, depthPitch);

  D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
  rtvDesc.Format = format;
  rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
  buf_->RegisterRTV(rtvDesc);

  D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
  srvDesc.Format = format;
  srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
  srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
  srvDesc.Texture2D.MipLevels = 1;
  buf_->RegisterSRV(srvDesc);

  return std::move(buf_);
}

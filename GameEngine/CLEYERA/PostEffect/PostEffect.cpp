#include "PostEffect.h"

void CLEYERA::Manager::PostEffectManager::Init() {

  auto device = Base::DX::DXManager::GetInstance()->GetDevice();

  vert_ = std::make_unique<Base::DX::DXBufferResource<Model3d::system::VertexForGPU>>();
  vert_->SetDevice(device);
  vert_->Init(3);
  vert_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
  vert_->CreateVertexBufferView();

  worldTransform_ = std::make_unique<Util::WorldTransform>();
  worldTransform_->SetScale(scale_);
  worldTransform_->SetRotate(rotate_);
  worldTransform_->SetTranslate(translate_);
  worldTransform_->WTCreate(1);
  worldTransform_->WorldMatUpdate();
}

void CLEYERA::Manager::PostEffectManager::Update() {

  vertData_.resize(3);

  vertData_[0].pos = {0.0f, 0.0f, 0.0f, 1.0f};
  vertData_[1].pos = {1280.0f, 0.0f, 0.0f, 1.0f};
  vertData_[2].pos = {0.0f, 720.0f, 0.0f, 1.0f};

  vert_->SetParam(vertData_);
  vert_->Update();
}

void CLEYERA::Manager::PostEffectManager::Draw() {

Manager::RenderManager::GetInstance();


}

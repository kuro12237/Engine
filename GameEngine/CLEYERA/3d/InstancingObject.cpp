#include "InstancingObject.h"

void CLEYERA::Model3d::InstancingGameObject::Init(uint32_t max) {

  auto device_ = Base::DX::DXManager::GetInstance()->GetDevice();
  this->worldMat_.resize(max);
  buf_ = std::make_unique<CLEYERA::Base::DX::DXBufferResource<
      CLEYERA::Util::system::forWorldMat>>();
  buf_->Init(max);
  buf_->SetDevice(device_);
  // バッファの作成
  buf_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
  buf_->CreateVertexBufferView();

  buf_->RegisterSRV();
}

void CLEYERA::Model3d::InstancingGameObject::Update() {

  buf_->Map();
  buf_->SetParam(worldMat_);
  buf_->UnMap();
}

void CLEYERA::Model3d::InstancingGameObject::Command(uint32_t num) {

buf_->GraphicsCommand(num);
}

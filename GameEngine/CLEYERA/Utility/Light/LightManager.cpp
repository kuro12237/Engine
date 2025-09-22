#include "LightManager.h"

void CLEYERA::Manager::LightManager::Init() {

  directionLight_ = std::make_shared<DirectionLight>();
  directionLight_->Init();

  this->pointData_ = std::make_shared<Base::DX::DXBufferResource<Component::System::PointLightForGPU>>();

  pointData_->SetDevice(Base::DX::DXManager::GetInstance()->GetDevice());
  pointData_->Init(32);
  pointData_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
  pointData_->RegisterSRV();
  pointLights_.resize(32);
}

void CLEYERA::Manager::LightManager::Update() {
  directionLight_->Update();

  pointData_->Map();
  pointData_->SetParam(this->pointLights_);
  pointData_->UnMap();
}

void CLEYERA::Manager::LightManager::ImGuiUpdate() { directionLight_->ImGuiUpdate(); }

void CLEYERA::Manager::LightManager::PointLightCommandBind(UINT num) {

  uint32_t handle = 0;
  auto srv = Base::DX::DXDescripterManager::GetInstance()->GetSRV().lock();
  auto command = Base::DX::DXCommandManager::GetInstace();
  handle = pointData_->GetSRVIndex();
  command->GraphicsDescripterTable(num, srv->GetGPUHandle(handle));


}

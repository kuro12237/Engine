#include "DIrectionLight.h"

void CLEYERA::Manager::DirectionLight::Init() {

   light_.direction = {0.0f, -1.0f, 0.0f};

   buf_ = std::make_unique<Base::DX::DXBufferResource<Graphics::system::SDirectionLight>>();
   buf_->SetDevice(Base::DX::DXManager::GetInstance()->GetDevice());
   buf_->Init();
   buf_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);

   commandManager_ = Base::DX::DXCommandManager::GetInstace();

}

void CLEYERA::Manager::DirectionLight::Update() { buf_->Map();
   buf_->SetParam(light_);
}

void CLEYERA::Manager::DirectionLight::ImGuiUpdate() {

   ImGui::Begin("Light");
   ImGui::DragFloat3("color", &light_.color.x, 0.1f);
   ImGui::DragFloat3("direction", &light_.direction.x, 0.1f);
   ImGui::End();

}

void CLEYERA::Manager::DirectionLight::CommandBind(UINT num) {

	commandManager_->GraphicsCommandCall(num, buf_->GetResource());

}

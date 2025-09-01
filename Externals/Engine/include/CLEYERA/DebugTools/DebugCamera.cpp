#include "DebugCamera.h"

void CLEYERA::DebugTools::DebugCamera::Init() {

   camera_ = std::make_shared<CLEYERA::Util::Camera>();
   camera_->Init();
   translate_.y = 4.0f;
   camera_->SetRotate(rotate_);
   camera_->SetTranslate(translate_);
   CLEYERA::Manager::CameraManager::GetInstance()->SetCamera(this->camera_);
   camera_->Update();
}

void CLEYERA::DebugTools::DebugCamera::Update() { camera_->Update(); }

void CLEYERA::DebugTools::DebugCamera::ImGuiUpdate() {

   ImGui::Begin("DebugCamera");
   ImGui::DragFloat3("r", &rotate_.x, 0.1f);
   ImGui::DragFloat3("t", &translate_.x, 1.0f);
   ImGui::End();
}

#include "CameraCompornent.h"

CLEYERA::Component::CameraCompornent::CameraCompornent() {

   cameraManager_ = CLEYERA::Manager::CameraManager::GetInstance();
   inputManager_ = CLEYERA::Manager::InputManager::GetInstance();


   camera_ = std::make_shared<CLEYERA::Util::Camera>();
   camera_->Init();
   camera_->SetRotate(rotate_);
   camera_->SetTranslate(translate_);
}

void CLEYERA::Component::CameraCompornent::ImGuiUpdate() {

   if (ImGui::TreeNode(name_.c_str())) {

      if (ImGui::TreeNode("Transform")) {

         ImGui::DragFloat3("R", &rotate_.x, 0.1f);
         ImGui::DragFloat3("T", &translate_.x, 0.1f);

         ImGui::TreePop();
      }

      if (jsonSystem_) {
         jsonSystem_->JsonImGuiUpdate();
      }

      if (imGuiFunc_) {
         imGuiFunc_(*this);
      }

      ImGui::TreePop();
   }
}

void CLEYERA::Component::CameraCompornent::CreateJsonSystem(const std::string &fileGroupName) {

   jsonSystem_ = std::make_unique<JsonCompornent>();
   jsonSystem_->CreateJson(name_, fileGroupName);
}

void CLEYERA::Component::CameraCompornent::CameraChange() { cameraManager_->SetCamera(camera_); }

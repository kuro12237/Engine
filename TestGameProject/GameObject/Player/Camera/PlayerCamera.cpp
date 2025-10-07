#include "PlayerCamera.h"

void PlayerCamera::Init() { this->CameraChange(); }

void PlayerCamera::Update() {

  translate_ = *p_playerPos_ + offset_;

  if (ImGui::TreeNode("camera")) {
    ImGui::DragFloat3("t", &translate_.x);

    ImGui::TreePop();
  }
}

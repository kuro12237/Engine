#include "Sun.h"

void Sun::Init() {
  this->Create();

  this->pos_ = {0.0f, 128.0f, -32.0f};
  rad_ = 256.0f;
}

void Sun::Update() {
  if (ImGui::TreeNode("light")) {
    ImGui::DragFloat3("t", &pos_.x);
    ImGui::DragFloat("rad", &this->rad_);

    ImGui::DragFloat("inte", &this->intensity_);
    ImGui::DragFloat("decay", &this->decay_);

    ImGui::TreePop();
  }
  this->TransfarGPU();
}

#include "TestPointLight.h"

void TestPointLight::Init() { Create(); }

void TestPointLight::Update() {

  if (ImGui::TreeNode("light")) {
    ImGui::DragFloat3("t", &pos_.x);
    ImGui::DragFloat("rad", &this->rad_);

    ImGui::DragFloat("inte", &this->intensity_);
    ImGui::DragFloat("decay", &this->decay_);

    ImGui::TreePop();
  }

  this->TransfarGPU();
}

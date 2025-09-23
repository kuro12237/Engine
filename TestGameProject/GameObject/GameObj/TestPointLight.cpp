#include "TestPointLight.h"

void TestPointLight::Init() {
  Create();
  center_ = Math::Vector::Vec2(pos_.x, pos_.z);
  rad_ = 64.0f;
  pos_.y = 8.0f;
  //color_ = Math::Vector::Vec4(Rand01(), Rand01(), Rand01(),1.0f);
}

void TestPointLight::Update() {

  if (ImGui::TreeNode("light")) {
    ImGui::DragFloat3("t", &pos_.x);
    ImGui::DragFloat("rad", &this->rad_);

    ImGui::DragFloat("inte", &this->intensity_);
    ImGui::DragFloat("decay", &this->decay_);

    ImGui::TreePop();
  }

  flame_ += 1.0f / 60.0f;
  angle_ += anglerSpeed_ * 1.0f / 10.0f;

  // 角度を 0〜2π に収める（数値安定）
  const float twoPi = 2.0f * 3.14159265358979323846f;
  if (angle_ > twoPi)
    angle_ -= twoPi;
  if (angle_ < 0.0f)
    angle_ += twoPi;

  // 円運動の座標計算
  auto pos = center_ +
             Math::Vector::Vec2(cos(angle_) * moveRad_, sin(angle_) * moveRad_);
  //pos_.x = pos.x;
  //pos_.z = pos.y;

  this->TransfarGPU();
}

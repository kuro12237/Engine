#include "ObjectCompornent.h"
#include "../Utility/ColliderSystem/ColliderSystem.h"
#include "Utility/Object/ObjectManager.h"

#include "../Utility/ColliderSystem/AABBCollider.h"
#include "../Utility/ColliderSystem/Collider.h"
#include "../Utility/ColliderSystem/OBBCollider.h"

CLEYERA::Component::ObjectComponent::ObjectComponent() {

  this->modelManager_ = CLEYERA::Manager::ModelManager::GetInstance();
  this->objectManager_ = CLEYERA::Manager::ObjectManager::GetInstance();
  this->renderManager_ = CLEYERA::Manager::RenderManager::GetInstance();
  this->inputManager_ = CLEYERA::Manager::InputManager::GetInstance();

  // デフォルトモデル
  uint32_t handleSphere = CLEYERA::Manager::ModelManager::GetInstance()->LoadModel(
      "Resources/Model/system/Sphere", "Sphere");
  modelHandle_ = handleSphere;

  // オブジェクトの生成、scaleなどのポインタセット
  gameObject_ = std::make_shared<CLEYERA::Model3d::Game3dObject>();
  gameObject_->Create(modelHandle_);
  gameObject_->SetScale(scale_);
  gameObject_->SetRotate(rotate_);
  gameObject_->SetTranslate(translate_);
  gameObject_->SetName(name_);

  // 各マネージャーへのセット
}

void CLEYERA::Component::ObjectComponent::ImGuiUpdate() {
  if (name_ == "") {
    return;
  }

  if (ImGui::TreeNode(name_.c_str())) {

    BaseParamImGuiDisply();

    ImGui::TreePop();
  }
}

void CLEYERA::Component::ObjectComponent::TransformUpdate() {

  using Vec3 = Math::Vector::Vec3;

  Vec3 totalForce = force_;
  force_ = {};

  //// 加速度 = 力 / 質量（F = ma → a = F/m）
  Vec3 acceleration = {};
  if (mass_ != 0.0f && mass_ >= 0.0f) {
    acceleration = totalForce * (1.0f / mass_);
  }

  // 積分：速度と位置の更新
  velocity_ += acceleration; // v = v0 + at
  translate_ += velocity_;   // p = p0 + vt

  // 摩擦（速度減衰）
  velocity_.x = velocity_.x * friction_;
  velocity_.z = velocity_.z * friction_;

  gameObject_->WorldMatUpdate();
}

void CLEYERA::Component::ObjectComponent::GravityUpdate(const float &g) { velocity_.y += g; }

void CLEYERA::Component::ObjectComponent::TerrainHit(const Math::Vector::Vec3 &pos) {
  velocity_.y = velocity_.y * -bounceFactor_;

  translate_.y = pos.y;
  translate_.y += 1.0f;
}

void CLEYERA::Component::ObjectComponent::BaseParamImGuiDisply() {
  if (ImGui::TreeNode("Transform")) {

    ImGui::DragFloat3("Scale", &scale_.x, 0.01f);
    ImGui::DragFloat3("Rotate", &rotate_.x, 0.01f);
    ImGui::DragFloat3("Translate", &translate_.x, 0.01f);
    ImGui::TreePop();
  }

  if (ImGui::TreeNode("force")) {
    ImGui::DragFloat("friction", &friction_, 0.1f, 0.0f, 1.0f);
    ImGui::DragFloat("mass", &mass_, 0.1f, 0.1f, 20.0f);
    ImGui::DragFloat("bounce", &bounceFactor_);
    ImGui::TreePop();
  }

  if (collider_) {
    collider_->ColliderImGuiUpdate(name_);
  }

  if (jsonSystem_) {
    jsonSystem_->JsonImGuiUpdate();
  }
}

void CLEYERA::Component::ObjectComponent::CreateCollider(Util::Collider::ColliderType type) {

  colliderSystem_ = CLEYERA::Manager::ColliderSystem::GetInstance();
  if (type == Util::Collider::ColliderType::OBB) {
    collider_ = std::make_shared<CLEYERA::Util::Collider::OBBCollider>();
    auto c = std::dynamic_pointer_cast<Util::Collider::OBBCollider>(collider_);

    c->SetCenter(&translate_);
    c->SetRotate(&rotate_);
    c->SetWorldMatrix(&gameObject_->GetMat());
    collider_->Create();
  }
  if (type == Util::Collider::ColliderType::AABB) {
    collider_ = std::make_shared<CLEYERA::Util::Collider::AABBCollider>();
    auto c = std::dynamic_pointer_cast<Util::Collider::AABBCollider>(collider_);

    c->SetCenter(&translate_);
    collider_->Create();
  }
}

void CLEYERA::Component::ObjectComponent::CreateJsonSystem(const std::string &fileGroupName) {

  jsonSystem_ = std::make_unique<JsonCompornent>();
  jsonSystem_->CreateJson(name_, fileGroupName);
}

#include "SpriteComponent.h"

void SpriteComponent::ImGuiUpdate() {

  if (ImGui::TreeNode(name_.c_str())) {

    this->TransformImGuiUpdate();

    if (GetJsonName()) {

      JsonImGuiUpdate();
    }
    ImGui::TreePop();
  }
}

void SpriteComponent::Draw() { sprite_->Draw(); }

void SpriteComponent::Create() {
  WTCreate(1);

  this->SetScale(this->scale_);
  this->SetRotate(this->rotate_);
  this->SetTranslate(this->translate_);

  this->sprite_ = std::make_shared<CLEYERA::Sprite2d::Sprite>();
  sprite_->Create();
  sprite_->SetAnker(this->anker);
  sprite_->SetSize(this->size);
  sprite_->SetTexHandle(handle_);

  sprite_->SetWorldbindFunc([this](UINT n) { this->BindWT(n); });
  sprite_->SetTexCooadPos(&LeftTop, &RightTop, &LeftBottom, &RightBottom);
}

void SpriteComponent::CreateJsonSystem(const std::string &fileGroupName) {
  CreateJson(name_, fileGroupName,CLEYERA::Manager::GlobalVariables::ResourcesGroupDirectory::UI);

  // 各パラメータの保存
  this->SetValue<Math::Vector::Vec3>(VAR_NAME(scale_), scale_);
  this->SetValue<Math::Vector::Vec3>(VAR_NAME(rotate_), rotate_);
  this->SetValue<Math::Vector::Vec3>(VAR_NAME(translate_), translate_);
  this->SetValue<Math::Vector::Vec2>(VAR_NAME(size), size);
  this->SetValue<Math::Vector::Vec2>(VAR_NAME(anker), anker);

  // 各パラメータの読込
  scale_ = this->GetValue<Math::Vector::Vec3>(VAR_NAME(scale_));
  rotate_ = this->GetValue<Math::Vector::Vec3>(VAR_NAME(rotate_));
  translate_ = this->GetValue<Math::Vector::Vec3>(VAR_NAME(translate_));
  size = this->GetValue<Math::Vector::Vec2>(VAR_NAME(size));
  anker = this->GetValue<Math::Vector::Vec2>(VAR_NAME(anker));
}

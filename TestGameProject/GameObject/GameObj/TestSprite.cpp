#include "TestSprite.h"

void TestSprite::Init() {
  this->name_ = VAR_NAME(TestSprite);

  this->Create();

  handle_ = this->texManager_->LoadPngTex("uvChecker");
}

void TestSprite::Update() {

#ifdef _DEBUG

  if (ImGui::TreeNode("TestSprite")) {

    this->TransformImGuiUpdate();
    ImGui::DragFloat2("size", &size_.x);
    ImGui::DragFloat4("color", &sprite_->ColorData().color_.x);

    ImGui::DragFloat2("LT", &this->LeftTop_.x,0.01f,0.0f,1.0f);
    ImGui::DragFloat2("LB", &this->LeftBottom_.x, 0.01f, 0.0f, 1.0f);
    ImGui::DragFloat2("RT", &this->RightTop_.x, 0.01f, 0.0f, 1.0f);
    ImGui::DragFloat2("RB", &this->RightBottom_.x, 0.01f, 0.0f, 1.0f);


    ImGui::TreePop();

  }

#endif // _DEBUG
  this->sprite_->Update();
  this->WorldMatUpdate();
}

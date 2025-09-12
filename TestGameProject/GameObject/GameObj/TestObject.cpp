#include "TestObject.h"

void TestObj::Init() {

  this->category_ = VAR_NAME(TestObj);
  uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/system/Sphere", "sphere");

  //当たり判定を作る際
  //CreateCollider(ColliderType::AABB);
  //collider_->SetHitCallFunc([this](std::weak_ptr<ObjectComponent> other) {this->OnCollision(other); });
  
}

void TestObj::Update() {

#ifdef _DEBUG
  ImGui::Text(name_.c_str());
  if (ImGui::TreeNode(name_.c_str())) {

    ImGui::DragFloat3("scale", &scale_.x);
    ImGui::DragFloat3("rotate", &rotate_.x);
    ImGui::DragFloat3("translate", &translate_.x);

    ImGui::DragFloat4("color", &this->colors_.color_.x);

    ImGui::TreePop();
  }
#endif // _DEBUG

  ///クラスを削除する際、下の状態に変更
  //this->SetMode(OBJ_MODE::REMOVE);
}

#include "TestObject.h"

void TestObj::Init() {

  this->category_ = VAR_NAME(TestObj);
  uint32_t modelHandle =
      modelManager_->LoadModel("Resources/Model/system/Sphere", "sphere");

  // 当たり判定を作る際
  // CreateCollider(ColliderType::AABB);
  // collider_->SetHitCallFunc([this](std::weak_ptr<ObjectComponent> other)
  // {this->OnCollision(other); });
}

void TestObj::Update() {

  lifeTime_ += 1.0f / 60.0f;
  if (lifeTime_ >= lifeMax_) {

    //SetMode(OBJ_MODE::REMOVE);
  }
}

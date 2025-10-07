#include "NormalBlock.h"

void NormalBlock::Init() {
  category_ = VAR_NAME(NormalBlock);
  CreateData();
}

void NormalBlock::Update() {
  auto c = std::dynamic_pointer_cast<CLEYERA::Util::Collider::AABBCollider>(
      collider_);
  auto &aabb = c->GetAABB_();
  aabb.min = scale_ * -1;
  aabb.max = scale_;
  TransformUpdate();
}

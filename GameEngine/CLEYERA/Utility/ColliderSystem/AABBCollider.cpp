#include "AABBCollider.h"

void CLEYERA::Util::Collider::AABBCollider::ColliderImGuiUpdate() {}

void CLEYERA::Util::Collider::AABBCollider::Create() {
  line_ = std::make_shared<CLEYERA::Model3d::Line3d>();
  line_->Init(12);

  colors_.resize(48);
  line_->SetLinePos(positions_);
  line_->SetLineColor(colors_);
  line_->SetRotate(lineRotate_);
  line_->SetTranslate(*aabb_.pos);
  line_->SetScale(scale_);
  line_->SetMat4x4(worldMatrix_);

  worldMatrix_.Identity();

  Util::Collider::system::Func::MakeLinesFromAABB(positions_, aabb_.min, aabb_.max);

}

void CLEYERA::Util::Collider::AABBCollider::Update() {
  aabb_.push = {};
  for (size_t i = 0; i < 48; i++) {

    colors_[i] = {1.0f, 0.0f, 0.0f, 1.0f};
  }
  Util::Collider::system::Func::MakeLinesFromAABB(positions_, aabb_.min, aabb_.max);

  line_->Update();
}

void CLEYERA::Util::Collider::AABBCollider::MortonUpdate() {}

void CLEYERA::Util::Collider::AABBCollider::ColliderImGuiUpdate(const std::string &name) { name; }

Math::Vector::Vec3
CLEYERA::Util::Collider::AABBCollider::CalcOverlapAABB(std::weak_ptr<Collider> other) {
  other;
  return Math::Vector::Vec3();
}

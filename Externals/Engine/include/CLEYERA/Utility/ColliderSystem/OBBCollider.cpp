#include "OBBCollider.h"

void CLEYERA::Util::Collider::OBBCollider::ColliderImGuiUpdate() {}

void CLEYERA::Util::Collider::OBBCollider::Create() {

  line_ = std::make_shared<CLEYERA::Model3d::Line3d>();
  line_->Init(24);

  colors_.resize(48);
  line_->SetLinePos(positions_);
  line_->SetLineColor(colors_);
  line_->SetRotate(*obb_.rotate);
  line_->SetTranslate(*obb_.center);
  line_->SetScale(obb_.size);
  line_->SetMat4x4(worldMatrix_);

  worldMatrix_.Identity();

  obb_.CalculateOrientations();
  Util::Collider::system::Func::MakeLinesFromOBB(positions_, obb_);
 
  line_->Update();
}

void CLEYERA::Util::Collider::OBBCollider::Update() {
  //center_ = *obb_.center;

  worldMatrix_ = Math::Matrix::Func::AffineMatrix(obb_.size, *obb_.rotate, *obb_.center);

  obb_.CalculateOrientations();

  if (!isHit_) {

    for (size_t i = 0; i < 48; i++) {

      colors_[i] = {1.0f, 0.0f, 0.0f, 1.0f};
    }
  } else {
    isHit_ = false;
  }

  line_->Update();
}

void CLEYERA::Util::Collider::OBBCollider::MortonUpdate() {

  Math::Vector::Vec3 min = *obb_.center;
  min -= obb_.size;
  Math::Vector::Vec3 max = *obb_.center;
  max += obb_.size;

  mortonNum_ = octree_->GetMortonNumber(min, max);
}

void CLEYERA::Util::Collider::OBBCollider::ColliderImGuiUpdate(const std::string &name) {
  name;

  if (ImGui::TreeNode("Collider")) {

    ImGui::DragFloat3("size", &obb_.size.x);

    ImGui::TreePop();
  }
}

Math::Vector::Vec3
CLEYERA::Util::Collider::OBBCollider::CalcOverlapAABB(std::weak_ptr<Collider> other) {
  auto obbB = std::dynamic_pointer_cast<OBBCollider>(other.lock());

  return Util::Collider::system::Func::PushOutAABB(this->obb_, obbB->GetOBB());
}

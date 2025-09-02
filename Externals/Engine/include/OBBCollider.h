#pragma once

#include "Collider.h"
#include "SCollider.h"

namespace CLEYERA {

namespace Util {

namespace Collider {

class OBBCollider : public Collider {
public:
  OBBCollider() {};
  ~OBBCollider() {};

  void ColliderImGuiUpdate() override;

  const system::OBB &GetOBB() const { return obb_; }

  void Create() override;

  void Update() override;

  void MortonUpdate() override;

  void ColliderImGuiUpdate(const std::string &name) override;
  Math::Vector::Vec3 CalcOverlapAABB(std::weak_ptr<Collider> other) override;

  void SetCenter(Math::Vector::Vec3 *center) { obb_.center = center; }
  void SetRotate(Math::Vector::Vec3 *rotate) { obb_.rotate = rotate; }
  void SetWorldMatrix(Math::Matrix::Mat4x4 *worldMatrix) { obb_.worldMatrix = worldMatrix; }
  void SetSize(const Math::Vector::Vec3 &size) { obb_.size = size; }

  system::OBB &GetOBB() { return obb_; }

private:
  system::OBB obb_ = {};
};

} // namespace Collider
} // namespace Util
} // namespace CLEYERA
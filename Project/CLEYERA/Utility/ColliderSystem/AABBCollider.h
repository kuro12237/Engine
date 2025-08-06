#pragma once

#include "Collider.h"
#include "SCollider.h"

namespace CLEYERA {

namespace Util {

namespace Collider {

class AABBCollider : public Collider {
public:
  AABBCollider() {};
  ~AABBCollider() {};

  void ColliderImGuiUpdate() override;

  void Create() override;

  void Update() override;

  void MortonUpdate() override;

  void ColliderImGuiUpdate(const std::string &name) override;
  Math::Vector::Vec3 CalcOverlapAABB(std::weak_ptr<Collider> other) override;

  const system::AABB &GetAABB() const { return aabb_; }
  system::AABB &GetAABB_() { return aabb_; }

  void SetCenter(Math::Vector::Vec3 *center) { aabb_.pos = center; }
  void SetSize(const Math::Vector::Vec3 &min, const Math::Vector::Vec3 max) {
    aabb_.min = min, aabb_.max = max;
  }

private:
  system::AABB aabb_ = {};
  Math::Vector::Vec3 lineRotate_{};
  Math::Vector::Vec3 scale_ = {1.0f, 1.0f, 1.0f};
};

} // namespace Collider
} // namespace Util
} // namespace CLEYERA
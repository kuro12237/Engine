#pragma once
#include "../../3d/Line3d/Line3d.h"
#include "ColliderFunc.h"
#include"Octree/Octree.h"

namespace CLEYERA {

namespace Component {

class ObjectComponent;
}

namespace Util {
namespace Collider {

enum class ColliderType { OBB ,AABB};

/// <summary>
/// コライダー
/// </summary>
class Collider {
public:
  Collider() {
    octree_ = std::make_unique<Octree>();
    octree_->Init();
  };
  virtual ~Collider() {};

  bool HitCall(std::weak_ptr<Component::ObjectComponent> other);

  virtual void ColliderImGuiUpdate() = 0;

  ColliderType GetColliderType() const { return type_; }

  virtual void Create() = 0;
  virtual void Update() = 0;
  virtual void ColliderImGuiUpdate(const std::string &name) = 0;
  virtual Math::Vector::Vec3 CalcOverlapAABB(std::weak_ptr<Collider> other) = 0;

  std::weak_ptr<CLEYERA::Model3d::Line3d> GetLine() const { return line_; }
  Math::Vector::Vec3 GetCenter() { return center_; }

  virtual void MortonUpdate();
  int32_t GetMortonNum() { return mortonNum_; }
  Octree *GetOctree() { return octree_.get(); }

  /// <summary>
  /// 当たった時の関数ポインタのセッター
  /// </summary>
  void SetHitCallFunc(
      std::function<void(std::weak_ptr<Component::ObjectComponent>)> func) {
    HitCallFunc = std::move(func);
  }

private:
  std::function<void(std::weak_ptr<Component::ObjectComponent> other)>
      HitCallFunc;

protected:
  ColliderType type_ = ColliderType::OBB;

  std::shared_ptr<CLEYERA::Model3d::Line3d> line_ = nullptr;
  std::vector<Math::Vector::Vec3> positions_ = {};
  std::vector<Math::Vector::Vec4> colors_ = {};

  Math::Vector::Vec3 center_{};
  Math::Matrix::Mat4x4 worldMatrix_ = {};
  bool isHit_ = false;

  int32_t mortonNum_ = 0;
  std::unique_ptr<Octree> octree_ = nullptr;

};

} // namespace Collider
} // namespace Util
} // namespace CLEYERA
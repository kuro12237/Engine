#pragma once

#include "../../pch/Pch.h"

namespace CLEYERA {

namespace Util {

namespace Collider {

namespace system {

struct OBB {

  Math::Vector::Vec3 *center = nullptr;
  Math::Vector::Vec3 *rotate{};

  Math::Vector::Vec3 size{1, 1, 1};

  std::array<Math::Vector::Vec3, 3> orientations{};

  Math::Matrix::Mat4x4 *worldMatrix = nullptr;
  void CalculateOrientations() {
    orientations[0] = {worldMatrix->m[0][0], worldMatrix->m[1][0],
                       worldMatrix->m[2][0]}; // X軸の方向ベクトル
    orientations[1] = {worldMatrix->m[0][1], worldMatrix->m[1][1],
                       worldMatrix->m[2][1]}; // Y軸の方向ベクトル
    orientations[2] = {worldMatrix->m[0][2], worldMatrix->m[1][2],
                       worldMatrix->m[2][2]}; // Z軸の方向ベクトル
  }
};

struct AABB {
  Math::Vector::Vec3 *pos = nullptr;
  Math::Vector::Vec3 min{-1.0f, -1.0f, -1.0f};
  Math::Vector::Vec3 max{1.0f, 1.0f, 1.0f};

  Math::Vector::Vec3 push{};

  void SetPush(Math::Vector::Vec3 &p) { push = p; }

  Math::Vector::Vec3 HalfSize() const { return (max - min) * 0.5f; }
  Math::Vector::Vec3 GetWorldMin() const { return *pos + min; }
  Math::Vector::Vec3 GetWorldMax() const { return *pos + max; }
  Math::Vector::Vec3 GetWorldCenter() const { return *pos + (min + max) * 0.5f; }
};

struct Triangle {

  enum class VertName { TOP = 0, LEFT = 1, RIGHT = 2 };

  std::array<Math::Vector::Vec3, 3> vertex;
  std::array<Math::Vector::Vec3, 3> edgeVec; // 辺ベクトル
  Math::Vector::Vec3 normal;
  float dot = 0; // 面の式ax+by+cz+d=0のd
  bool contains(const Math::Vector::Vec3 &p);

  float getY(const Math::Vector::Vec3 &p);
};

} // namespace system
} // namespace Collider
} // namespace Util
} // namespace CLEYERA
#pragma once

#include <json.hpp>

namespace Math::Vector {

/// <summary>
/// Vector2
/// </summary>
struct Vec2 {

  float x = 0.0f, y = 0.0f;

  void Init() { x = 0.0f, y = 0.0f; }

  // 加算オペレーター
  Vec2 operator+(const Vec2 &other) const {
    return Vec2{x + other.x, y + other.y};
  }

  // 減算オペレーター
  Vec2 operator-(const Vec2 &other) const {
    return Vec2{x - other.x, y - other.y};
  }

  // 乗算オペレーター
  Vec2 operator*(const Vec2 &other) const {
    return Vec2{x * other.x, y * other.y};
  }
  // *= オペレーター
  Vec2 &operator*=(const Vec2 &other) {
    x *= other.x;
    y *= other.y;
    return *this;
  }

  // 割り算オペレーター
  Vec2 operator/(const Vec2 &other) const {
    return Vec2{x / other.x, y / other.y};
  }

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(Vec2, x, y);
};

/// <summary>
/// Vector3
/// </summary>
struct Vec3 {
  float x = 0.0f, y = 0.0f, z = 0.0f;

  void Init() { x = 0.0f, y = 0.0f, z = 0.0f; }
  // 加算オペレーター
  Vec3 operator+(const Vec3 &other) const {
    return Vec3{x + other.x, y + other.y, z + other.z};
  }

  // 減算オペレーター
  Vec3 operator-(const Vec3 &other) const {
    return Vec3{x - other.x, y - other.y, z - other.z};
  }

  // 乗算オペレーター
  Vec3 operator*(const Vec3 &other) const {
    return Vec3{x * other.x, y * other.y, z * other.z};
  }

  // 割り算オペレーター
  Vec3 operator/(const Vec3 &other) const {
    return Vec3{x / other.x, y / other.y, z / other.z};
  }

  // 新しい乗算オペレーター
  Vec3 operator*(float scalar) const {
    return Vec3{x * scalar, y * scalar, z * scalar};
  }

  // 新しい乗算オペレーター
  Vec3 operator/(float scalar) const {
    return Vec3{x / scalar, y / scalar, z / scalar};
  }

  // += オペレーター
  Vec3 &operator+=(const Vec3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  // -= オペレーター
  Vec3 &operator-=(const Vec3 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }

  // *= オペレーター
  Vec3 &operator*=(const Vec3 &other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
  }

  // /= オペレーター
  Vec3 &operator/=(const Vec3 &other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
  }

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(Vec3, x, y, z);
};

/// <summary>
/// Vector4
/// </summary>
struct Vec4 {
  float x = 0, y = 0, z = 0, w = 0;

  void Init() { x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f; }

  // 加算オペレーター
  Vec4 operator+(const Vec4 &other) const {
    return Vec4{x + other.x, y + other.y, z + other.z, w + other.w};
  }

  // 減算オペレーター
  Vec4 operator-(const Vec4 &other) const {
    return Vec4{x - other.x, y - other.y, z - other.z, w - other.w};
  }

  // 乗算オペレーター
  Vec4 operator*(const Vec4 &other) const {
    return Vec4{x * other.x, y * other.y, z * other.z, w * other.w};
  }

  // 割り算オペレーター
  Vec4 operator/(const Vec4 &other) const {
    return Vec4{x / other.x, y / other.y, z / other.z, w / other.w};
  }

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(Vec4, x, y, z, w);
};

} // namespace Math::Vector
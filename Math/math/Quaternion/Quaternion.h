#pragma once

namespace Math::Quaternon {

/// <summary>
/// 四元数
/// </summary>
struct Qua {

  float x, y, z, w;

  void Identity() { x = 0.0f, y = 0.0f, z = 0.0f, w = 1.0f; }


  // 乗算オペレーター
  Qua operator*(const Qua &rhs) const {
    Qua result{};
    result.w = w * rhs.w - x * rhs.x - rhs.y * y - z * rhs.z;
    result.x = y * rhs.z - z * rhs.y + rhs.w * x + w * rhs.x;
    result.y = z * rhs.x - x * rhs.z + rhs.w * y + w * rhs.y;
    result.z = x * rhs.y - y * rhs.x + rhs.w * z + w * rhs.z;
    return result;
  }

};

} // namespace Math::Quaternon

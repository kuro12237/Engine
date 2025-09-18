#pragma once
#include "SMatrix.h"
#include "SVector.h"

#include <cmath>
#include <numbers>

#include <algorithm>

namespace Math::Vector::Func {

/// <summary>
/// 2つの3次元ベクトルのドット積を計算する関数
/// </summary>
float Dot(const Vec3 &v1, const Vec3 &v2);

/// <summary>
/// コサインとサインの比を求める関数 (余接)
/// </summary>
/// <param name="theta"></param>
/// <returns></returns>
float Cot(float theta);

/// <summary>
/// 度数法の角度をラジアンに変換する関数
/// </summary>
template <typename T> T degreesToRadians(T degrees);

/// <summary>
/// 2次元ベクトルの長さを計算する関数
/// </summary>
float Length(const Vec2 &v);

/// <summary>
/// 3次元ベクトルの長さを計算する関数
/// </summary>
float Length(const Vec3 &v);

/// <summary>
/// 値を正規化する関数
/// </summary>
Vec3 Normalize(const Vec3 &v);

/// <summary>
/// 2つの3次元ベクトルのクロス積を計算する関数
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vec3 Cross(const Vec3 &v1, const Vec3 &v2);

/// <summary>
/// 3次元ベクトルを4x4行列で変換する関数
/// </summary>
Vec3 TransformNormal(const Vec3 &v, const Matrix::Mat4x4 &m);

template <typename T> T degreesToRadians(T degrees) {
  return degrees * (float(std::numbers::pi) / 180.0f);
}

namespace Easing {
constexpr float PI = 3.14159265358979323846f;

template <typename T> T Lerp(const T &a, const T &b, const float t) {

  T P = (b - a) * t;
  P = a + P;
  return P;
}

// Sine
template <typename T> inline T EaseInSine(const T &a, const T &b, float t) {
  float k = 1.0f - std::cos((t * PI) / 2.0f);
  return a + (b - a) * k;
}
template <typename T> inline T EaseOutSine(const T &a, const T &b, float t) {
  float k = std::sin((t * PI) / 2.0f);
  return a + (b - a) * k;
}
template <typename T> inline T EaseInOutSine(const T &a, const T &b, float t) {
  float k = 0.5f * (1.0f - std::cos(PI * t));
  return a + (b - a) * k;
}

// Quadratic
template <typename T> inline T EaseInQuad(const T &a, const T &b, float t) {
  float k = t * t;
  return a + (b - a) * k;
}
template <typename T> inline T EaseOutQuad(const T &a, const T &b, float t) {
  float k = 1.0f - (1.0f - t) * (1.0f - t);
  return a + (b - a) * k;
}
template <typename T> inline T EaseInOutQuad(const T &a, const T &b, float t) {
  float k = (t < 0.5f) ? (2.0f * t * t)
                       : (1.0f - std::pow(-2.0f * t + 2.0f, 2.0f) / 2.0f);
  return a + (b - a) * k;
}

// Cubic
template <typename T> inline T EaseInCubic(const T &a, const T &b, float t) {
  float k = t * t * t;
  return a + (b - a) * k;
}
template <typename T> inline T EaseOutCubic(const T &a, const T &b, float t) {
  float k = 1.0f - std::pow(1.0f - t, 3.0f);
  return a + (b - a) * k;
}
template <typename T> inline T EaseInOutCubic(const T &a, const T &b, float t) {
  float k = (t < 0.5f) ? (4.0f * t * t * t)
                       : (1.0f - std::pow(-2.0f * t + 2.0f, 3.0f) / 2.0f);
  return a + (b - a) * k;
}

// Back
template <typename T>
inline T EaseInBack(const T &a, const T &b, float t, float s = 1.70158f) {
  float k = t * t * ((s + 1.0f) * t - s);
  return a + (b - a) * k;
}
template <typename T>
inline T EaseOutBack(const T &a, const T &b, float t, float s = 1.70158f) {
  float u = t - 1.0f;
  float k = u * u * ((s + 1.0f) * u + s) + 1.0f;
  return a + (b - a) * k;
}
template <typename T>
inline T EaseInOutBack(const T &a, const T &b, float t, float s = 1.70158f) {
  float s2 = s * 1.525f;
  float k;
  if (t < 0.5f) {
    float u = 2.0f * t;
    k = 0.5f * (u * u * ((s2 + 1.0f) * u - s2));
  } else {
    float u = 2.0f * t - 2.0f;
    k = 0.5f * (u * u * ((s2 + 1.0f) * u + s2) + 2.0f);
  }
  return a + (b - a) * k;
}

// Elastic
template <typename T> inline T EaseInElastic(const T &a, const T &b, float t) {
  if (t == 0.0f)
    return a;
  if (t == 1.0f)
    return b;
  float p = 0.3f;
  float s = p / 4.0f;
  float u = t - 1.0f;
  float k = -std::pow(2.0f, 10.0f * u) * std::sin((u - s) * (2.0f * PI) / p);
  return a + (b - a) * k;
}
template <typename T> inline T EaseOutElastic(const T &a, const T &b, float t) {
  if (t == 0.0f)
    return a;
  if (t == 1.0f)
    return b;
  float p = 0.3f;
  float s = p / 4.0f;
  float k =
      std::pow(2.0f, -10.0f * t) * std::sin((t - s) * (2.0f * PI) / p) + 1.0f;
  return a + (b - a) * k;
}
template <typename T>
inline T EaseInOutElastic(const T &a, const T &b, float t) {
  if (t == 0.0f)
    return a;
  if (t == 1.0f)
    return b;
  float p = 0.45f;
  float s = p / 4.0f;
  float u = t * 2.0f;
  float k;
  if (u < 1.0f) {
    float v = u - 1.0f;
    k = -0.5f * std::pow(2.0f, 10.0f * v) * std::sin((v - s) * (2.0f * PI) / p);
  } else {
    float v = u - 1.0f;
    k = std::pow(2.0f, -10.0f * v) * std::sin((v - s) * (2.0f * PI) / p) *
            0.5f +
        1.0f;
  }
  return a + (b - a) * k;
}

// Bounce
inline float BounceOutScalar(float t) {
  const float n1 = 7.5625f;
  const float d1 = 2.75f;
  if (t < 1.0f / d1) {
    return n1 * t * t;
  } else if (t < 2.0f / d1) {
    float u = t - 1.5f / d1;
    return n1 * u * u + 0.75f;
  } else if (t < 2.5f / d1) {
    float u = t - 2.25f / d1;
    return n1 * u * u + 0.9375f;
  } else {
    float u = t - 2.625f / d1;
    return n1 * u * u + 0.984375f;
  }
}

template <typename T> inline T EaseOutBounce(const T &a, const T &b, float t) {
  float k = BounceOutScalar(t);
  return a + (b - a) * k;
}
template <typename T> inline T EaseInBounce(const T &a, const T &b, float t) {
  float k = 1.0f - BounceOutScalar(1.0f - t);
  return a + (b - a) * k;
}
template <typename T>
inline T EaseInOutBounce(const T &a, const T &b, float t) {
  float k;
  if (t < 0.5f)
    k = 0.5f * (1.0f - BounceOutScalar(1.0f - 2.0f * t));
  else
    k = 0.5f * (BounceOutScalar(2.0f * t - 1.0f) + 1.0f);
  return a + (b - a) * k;
}

} // namespace Easing

} // namespace Math::Vector::Func
#pragma once
#include "../Matrix/SMatrix.h"
#include "SVector.h"

#include <cmath>
#include <numbers>

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
float degreesToRadians(float degrees);

/// <summary>
/// 2次元ベクトルの長さを計算する関数
/// </summary>
float Length(const Vec2 &v);

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
/// 線形補間を行う関数
/// </summary>
template <typename T> T Lerp(const T &a, const T &b, const float t);

/// <summary>
/// 3次元ベクトルを4x4行列で変換する関数
/// </summary>
Vec3 TransformNormal(const Vec3 &v, const Matrix::Mat4x4 &m);

template <typename T> T Lerp(const T &a, const T &b, const float t) {

  T P = (b - a) * t;
  P = a + P;
  return P;
}

} // namespace Math::Vector::Func
#pragma once
#include "../Vector/VectorFunc.h"
#include "SMatrix.h"

namespace Math::Matrix::Func {

/// <summary>
/// 3x4行列単位行列
/// </summary>
/// <returns></returns>
Mat3x4 Identity3x4();

/// <summary>
/// 掛け算
/// </summary>
/// <param name="mat1"></param>
/// <param name="mat2"></param>
/// <returns></returns>
Mat4x4 Multiply(const Mat4x4 &mat1, const Mat4x4 &mat2);



Mat4x4 Inverse(const Mat4x4 &m);

/// <summary>
/// ビューポート行列を作成する関数
/// </summary>
Mat4x4 ViewportMatrix(float left, float top, float width, float height,
                      float minDepth, float maxDepth);

/// <summary>
/// 透視投影行列を作成する関数
/// </summary>
Mat4x4 PerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip,
                            float farClip);

/// <summary>
/// 正射影行列を作成する関数
/// </summary>
Mat4x4 OrthographicMatrix(float left, float top, float right, float bottom,
                          float nearClip, float farClip);

/// <summary>
/// スケール行列を作成する関数
/// </summary>
Mat4x4 ScaleMatrix(const Math::Vector::Vec3 &s);

/// <summary>
/// 移動行列を作成する関数
/// </summary>
Mat4x4 TranslateMatrix(const Math::Vector::Vec3 &t);

/// <summary>
/// X軸周りの回転行列を作成する関数
/// </summary>
Mat4x4 RotateXMatrix(float theta);

/// <summary>
/// Y軸周りの回転行列を作成する関数
/// </summary>
Mat4x4 RotateYMatrix(float theta);

/// <summary>
/// Z軸周りの回転行列を作成する関数
/// </summary>
Mat4x4 RotateZMatrix(float theta);

/// <summary>
/// XYZ軸の回転を行う行列を作成する関数
/// </summary>
Mat4x4 RotateXYZMatrix(const Math::Vector::Vec3 &rotate);

/// <summary>
/// アフィン変換行列を作成する関数（スケール、回転、移動を含む）
/// </summary>
Mat4x4 AffineMatrix(const Math::Vector::Vec3 &Sv,
                       const Math::Vector::Vec3 &Rv,
                       const Math::Vector::Vec3 &Tv);


} // namespace Math::Matrix::Func
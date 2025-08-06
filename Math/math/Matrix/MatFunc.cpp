#include "MatFunc.h"

using namespace Math::Matrix::Func;
using namespace Math::Matrix;

Mat3x4 Math::Matrix::Func::Identity3x4() {
  return {{
      {1, 0, 0, 0}, // X軸
      {0, 1, 0, 0}, // Y軸
      {0, 0, 1, 0}  // Z軸
  }};
}

Mat4x4 Math::Matrix::Func::Multiply(const Mat4x4 &m1, const Mat4x4 &m2) {
  Mat4x4 result = {};
  result.m[0][0] = (m1.m[0][0] * m2.m[0][0]) + (m1.m[0][1] * m2.m[1][0]) +
                   (m1.m[0][2] * m2.m[2][0]) + (m1.m[0][3] * m2.m[3][0]);
  result.m[0][1] = (m1.m[0][0] * m2.m[0][1]) + (m1.m[0][1] * m2.m[1][1]) +
                   (m1.m[0][2] * m2.m[2][1]) + (m1.m[0][3] * m2.m[3][1]);
  result.m[0][2] = (m1.m[0][0] * m2.m[0][2]) + (m1.m[0][1] * m2.m[1][2]) +
                   (m1.m[0][2] * m2.m[2][2]) + (m1.m[0][3] * m2.m[3][2]);
  result.m[0][3] = (m1.m[0][0] * m2.m[0][3]) + (m1.m[0][1] * m2.m[1][3]) +
                   (m1.m[0][2] * m2.m[2][3]) + (m1.m[0][3] * m2.m[3][3]);

  result.m[1][0] = (m1.m[1][0] * m2.m[0][0]) + (m1.m[1][1] * m2.m[1][0]) +
                   (m1.m[1][2] * m2.m[2][0]) + (m1.m[1][3] * m2.m[3][0]);
  result.m[1][1] = (m1.m[1][0] * m2.m[0][1]) + (m1.m[1][1] * m2.m[1][1]) +
                   (m1.m[1][2] * m2.m[2][1]) + (m1.m[1][3] * m2.m[3][1]);
  result.m[1][2] = (m1.m[1][0] * m2.m[0][2]) + (m1.m[1][1] * m2.m[1][2]) +
                   (m1.m[1][2] * m2.m[2][2]) + (m1.m[1][3] * m2.m[3][2]);
  result.m[1][3] = (m1.m[1][0] * m2.m[0][3]) + (m1.m[1][1] * m2.m[1][3]) +
                   (m1.m[1][2] * m2.m[2][3]) + (m1.m[1][3] * m2.m[3][3]);

  result.m[2][0] = (m1.m[2][0] * m2.m[0][0]) + (m1.m[2][1] * m2.m[1][0]) +
                   (m1.m[2][2] * m2.m[2][0]) + (m1.m[2][3] * m2.m[3][0]);
  result.m[2][1] = (m1.m[2][0] * m2.m[0][1]) + (m1.m[2][1] * m2.m[1][1]) +
                   (m1.m[2][2] * m2.m[2][1]) + (m1.m[2][3] * m2.m[3][1]);
  result.m[2][2] = (m1.m[2][0] * m2.m[0][2]) + (m1.m[2][1] * m2.m[1][2]) +
                   (m1.m[2][2] * m2.m[2][2]) + (m1.m[2][3] * m2.m[3][2]);
  result.m[2][3] = (m1.m[2][0] * m2.m[0][3]) + (m1.m[2][1] * m2.m[1][3]) +
                   (m1.m[2][2] * m2.m[2][3]) + (m1.m[2][3] * m2.m[3][3]);

  result.m[3][0] = (m1.m[3][0] * m2.m[0][0]) + (m1.m[3][1] * m2.m[1][0]) +
                   (m1.m[3][2] * m2.m[2][0]) + (m1.m[3][3] * m2.m[3][0]);
  result.m[3][1] = (m1.m[3][0] * m2.m[0][1]) + (m1.m[3][1] * m2.m[1][1]) +
                   (m1.m[3][2] * m2.m[2][1]) + (m1.m[3][3] * m2.m[3][1]);
  result.m[3][2] = (m1.m[3][0] * m2.m[0][2]) + (m1.m[3][1] * m2.m[1][2]) +
                   (m1.m[3][2] * m2.m[2][2]) + (m1.m[3][3] * m2.m[3][2]);
  result.m[3][3] = (m1.m[3][0] * m2.m[0][3]) + (m1.m[3][1] * m2.m[1][3]) +
                   (m1.m[3][2] * m2.m[2][3]) + (m1.m[3][3] * m2.m[3][3]);

  return result;
}

Mat4x4 Math::Matrix::Func::Inverse(const Mat4x4 &m) {
  Mat4x4 result = {};
  float determinant = m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] +
                      m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] +
                      m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] -

                      m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] -
                      m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] -
                      m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2] -

                      m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] -
                      m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] -
                      m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2] +

                      m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] +
                      m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] +
                      m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] +

                      m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] +
                      m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] +
                      m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] -

                      m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] -
                      m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] -
                      m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2] -

                      m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] -
                      m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] -
                      m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0] +

                      m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] +
                      m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] +
                      m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];
  assert(determinant != 0.0f);
  float determinantRecp = 1.0f / determinant;

  result.m[0][0] =
      (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] +
       m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] -
       m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]) *
      determinantRecp;
  result.m[0][1] =
      (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] -
       m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] +
       m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]) *
      determinantRecp;
  result.m[0][2] =
      (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] +
       m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] -
       m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]) *
      determinantRecp;
  result.m[0][3] =
      (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] -
       m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] +
       m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]) *
      determinantRecp;

  result.m[1][0] =
      (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] -
       m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] +
       m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]) *
      determinantRecp;
  result.m[1][1] =
      (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] +
       m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] -
       m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]) *
      determinantRecp;
  result.m[1][2] =
      (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] -
       m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] +
       m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]) *
      determinantRecp;
  result.m[1][3] =
      (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] +
       m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] -
       m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]) *
      determinantRecp;

  result.m[2][0] =
      (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] +
       m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] -
       m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]) *
      determinantRecp;
  result.m[2][1] =
      (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] -
       m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] +
       m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]) *
      determinantRecp;
  result.m[2][2] =
      (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] +
       m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] -
       m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]) *
      determinantRecp;
  result.m[2][3] =
      (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] -
       m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] +
       m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]) *
      determinantRecp;

  result.m[3][0] =
      (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] -
       m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] +
       m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]) *
      determinantRecp;
  result.m[3][1] =
      (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] +
       m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] -
       m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]) *
      determinantRecp;
  result.m[3][2] =
      (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] -
       m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] +
       m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]) *
      determinantRecp;
  result.m[3][3] =
      (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] +
       m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] -
       m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]) *
      determinantRecp;

  return result;
}

Mat4x4 Math::Matrix::Func::ViewportMatrix(float left, float top, float width,
                                          float height, float minDepth,
                                          float maxDepth) {
  Mat4x4 result = {};
  result.m[0][0] = width / 2.0f;
  result.m[0][1] = 0.0f;
  result.m[0][2] = 0.0f;
  result.m[0][3] = 0.0f;

  result.m[1][0] = 0.0f;
  result.m[1][1] = -(height / 2.0f);
  result.m[1][2] = 0.0f;
  result.m[1][3] = 0.0f;

  result.m[2][0] = 0.0f;
  result.m[2][1] = 0.0f;
  result.m[2][2] = maxDepth - minDepth;
  result.m[2][3] = 0.0f;

  result.m[3][0] = left + (width / 2.0f);
  result.m[3][1] = top + (height / 2.0f);
  result.m[3][2] = minDepth;
  result.m[3][3] = 1.0f;

  return result;
}

Mat4x4 Math::Matrix::Func::PerspectiveFovMatrix(float fovY, float aspectRatio,
                                                float nearClip, float farClip) {
  Mat4x4 result = {};
  float theta = fovY / 2.0f;

  result.m[0][0] = (1.0f / aspectRatio) * Vector::Func::Cot(theta);
  result.m[0][1] = 0;
  result.m[0][2] = 0;
  result.m[0][3] = 0;

  result.m[1][0] = 0;
  result.m[1][1] = Vector::Func::Cot(theta);
  result.m[1][2] = 0;
  result.m[1][3] = 0;

  result.m[2][0] = 0;
  result.m[2][1] = 0;
  result.m[2][2] = farClip / (farClip - nearClip);
  result.m[2][3] = 1;

  result.m[3][0] = 0;
  result.m[3][1] = 0;
  result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
  result.m[3][3] = 0;

  return result;
}

Mat4x4 Math::Matrix::Func::OrthographicMatrix(float left, float top,
                                              float right, float bottom,
                                              float nearClip, float farClip) {
  Mat4x4 result = {};
  result.m[0][0] = 2.0f / (right - left);
  result.m[0][1] = 0;
  result.m[0][2] = 0;
  result.m[0][3] = 0;

  result.m[1][0] = 0;
  result.m[1][1] = 2.0f / (top - bottom);
  result.m[1][2] = 0;
  result.m[1][3] = 0;

  result.m[2][0] = 0;
  result.m[2][1] = 0;
  result.m[2][2] = (1 / farClip - nearClip);
  result.m[2][3] = 0;

  result.m[3][0] = (left + right) / (left - right);
  result.m[3][1] = (top + bottom) / (bottom - top);
  result.m[3][2] = nearClip / (nearClip - farClip);
  result.m[3][3] = 1;

  return result;
}

Mat4x4 Math::Matrix::Func::ScaleMatrix(const Math::Vector::Vec3 &s) {
  Mat4x4 result = {};
  result.m[0][0] = s.x;
  result.m[0][1] = 0.0f;
  result.m[0][2] = 0.0f;
  result.m[0][3] = 0.0f;

  result.m[1][0] = 0.0f;
  result.m[1][1] = s.y;
  result.m[1][2] = 0.0f;
  result.m[1][3] = 0.0f;

  result.m[2][0] = 0.0f;
  result.m[2][1] = 0.0f;
  result.m[2][2] = s.z;
  result.m[2][3] = 0.0f;

  result.m[3][0] = 0.0f;
  result.m[3][1] = 0.0f;
  result.m[3][2] = 0.0f;
  result.m[3][3] = 1.0f;

  return result;
}

Mat4x4 Math::Matrix::Func::TranslateMatrix(const Math::Vector::Vec3 &t) {
  Mat4x4 result = {};
  result.m[0][0] = 1.0f;
  result.m[0][1] = 0.0f;
  result.m[0][2] = 0.0f;
  result.m[0][3] = 0.0f;

  result.m[1][0] = 0.0f;
  result.m[1][1] = 1.0f;
  result.m[1][2] = 0.0f;
  result.m[1][3] = 0.0f;

  result.m[2][0] = 0.0f;
  result.m[2][1] = 0.0f;
  result.m[2][2] = 1.0f;
  result.m[2][3] = 0.0f;

  result.m[3][0] = t.x;
  result.m[3][1] = t.y;
  result.m[3][2] = t.z;
  result.m[3][3] = 1.0f;

  return result;
}

Mat4x4 Math::Matrix::Func::RotateXMatrix(float theta) {
  Mat4x4 result = {};

  result.m[0][0] = 1.0f;
  result.m[0][1] = 0.0f;
  result.m[0][2] = 0.0f;
  result.m[0][3] = 0.0f;

  result.m[1][0] = 0.0f;
  result.m[1][1] = std::cos(theta);
  result.m[1][2] = std::sin(theta);
  result.m[1][3] = 0.0f;

  result.m[2][0] = 0.0f;
  result.m[2][1] = -(std::sin(theta));
  result.m[2][2] = std::cos(theta);
  result.m[2][3] = 0.0f;

  result.m[3][0] = 0.0f;
  result.m[3][1] = 0.0f;
  result.m[3][2] = 0.0f;
  result.m[3][3] = 1.0f;

  return result;
}

Mat4x4 Math::Matrix::Func::RotateYMatrix(float theta) {
  Mat4x4 result = {};

  result.m[0][0] = std::cos(theta);
  result.m[0][1] = 0.0f;
  result.m[0][2] = -(std::sin(theta));
  result.m[0][3] = 0.0f;

  result.m[1][0] = 0.0f;
  result.m[1][1] = 1.0f;
  result.m[1][2] = 0.0f;
  result.m[1][3] = 0.0f;

  result.m[2][0] = std::sin(theta);
  result.m[2][1] = 0.0f;
  result.m[2][2] = std::cos(theta);
  result.m[2][3] = 0.0f;

  result.m[3][0] = 0.0f;
  result.m[3][1] = 0.0f;
  result.m[3][2] = 0.0f;
  result.m[3][3] = 1.0f;

  return result;
}

Mat4x4 Math::Matrix::Func::RotateZMatrix(float theta) {
  Mat4x4 result = {};

  result.m[0][0] = std::cos(theta);
  result.m[0][1] = std::sin(theta);
  result.m[0][2] = 0.0f;
  result.m[0][3] = 0.0f;

  result.m[1][0] = -(std::sin(theta));
  result.m[1][1] = std::cos(theta);
  result.m[1][2] = 0.0f;
  result.m[1][3] = 0.0f;

  result.m[2][0] = 0.0f;
  result.m[2][1] = 0.0f;
  result.m[2][2] = 1.0f;
  result.m[2][3] = 0.0f;

  result.m[3][0] = 0.0f;
  result.m[3][1] = 0.0f;
  result.m[3][2] = 0.0f;
  result.m[3][3] = 1.0f;

  return result;
}

Mat4x4 Math::Matrix::Func::RotateXYZMatrix(const Math::Vector::Vec3 &rotate) {
  Mat4x4 result;

  Mat4x4 rotateMatrixX = RotateXMatrix(rotate.x);
  Mat4x4 rotateMatrixY = RotateYMatrix(rotate.y);
  Mat4x4 rotateMatrixZ = RotateZMatrix(rotate.z);

  result = Multiply(rotateMatrixX, Multiply(rotateMatrixY, rotateMatrixZ));

  return result;
}

Mat4x4 Math::Matrix::Func::AffineMatrix(const Math::Vector::Vec3 &Sv,
                                        const Math::Vector::Vec3 &Rv,
                                        const Math::Vector::Vec3 &Tv) {
  Mat4x4 result;

  // S
  Mat4x4 scaleMatrix;
  scaleMatrix = ScaleMatrix(Sv);
  // R
  Mat4x4 rotateMatrix;
  rotateMatrix = RotateXYZMatrix(Rv);
  // T
  Mat4x4 translateMatrix;
  translateMatrix = TranslateMatrix(Tv);

  result = Multiply(scaleMatrix, Multiply(rotateMatrix, translateMatrix));

  return result;
}

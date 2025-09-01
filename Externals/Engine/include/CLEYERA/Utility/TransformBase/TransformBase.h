#pragma once
#include "../../DX/DXBufferResource/DXBufferResource.h"
#include "../../pch/Pch.h"

namespace CLEYERA {

namespace Util {

namespace system {

struct SCamera {

   Math::Matrix::Mat4x4 matProj_ = {};
   Math::Matrix::Mat4x4 mtxProjInv_ = {};
   Math::Matrix::Mat4x4 matView_ = {};
   Math::Matrix::Mat4x4 mtxViewInv_ = {};
   Math::Matrix::Mat4x4 mtxVP_ = {};
   Math::Matrix::Mat4x4 orthographic = {};
   Math::Vector::Vec4 cameraPos_ = {};
};
struct forWorldMat {
   Math::Matrix::Mat4x4 worldMat_ = {};
   Math::Matrix::Mat4x4 worldMatInv_ = {};
   Math::Matrix::Mat4x4 WPV_ = {};
   Math::Vector::Vec4 worldPos_ = {};
};
} // namespace system

class TransformBase {
 public:
   TransformBase();
   virtual ~TransformBase() {};

   void WorldMatUpdate();

   void TransformImGuiUpdate();

   Math::Vector::Vec3 GetWorldPos();
   Math::Vector::Vec3 GetWorldRotate();
   Math::Vector::Vec3 GetWorldScale();

   Math::Vector::Vec3 GetScale() const { return *scale_; }
   Math::Vector::Vec3 GetRotate() const { return *rotate_; }
   Math::Vector::Vec3 GetTranslate() const { return *translate_; }
   Math::Matrix::Mat4x4 &GetMat() { return mat_; }
   Math::Matrix::Mat3x4 &GetMat3x4() { return forGpumat_; }

   void SetScale(Math::Vector::Vec3 &s) { scale_ = &s; }
   void SetRotate(Math::Vector::Vec3 &r) { rotate_ = &r; }
   void SetTranslate(Math::Vector::Vec3 &t) { translate_ = &t; }
   void SetMat4x4(Math::Matrix::Mat4x4 &m) { mat_ = m; }

   void SetParent(std::weak_ptr<TransformBase> p) { parent_ = p; };
 protected:
   Math::Vector::Vec3 *scale_ = nullptr;
   Math::Vector::Vec3 *rotate_ = nullptr;
   Math::Quaternon::Qua *qua_ = nullptr;
   Math::Vector::Vec3 *translate_ = nullptr;

   Math::Matrix::Mat4x4 mat_ = {};

   std::weak_ptr<TransformBase> parent_;
 private:
  
 
   // ray
   Math::Matrix::Mat3x4 forGpumat_ = {};
};

} // namespace Util
} // namespace CLEYERA
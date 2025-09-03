#pragma once
#include "../../DX/DXManager.h"
#include "../../WIn/WinApp.h"
#include "../../pch/Pch.h"
#include "../TransformBase/TransformBase.h"

namespace CLEYERA {
namespace Util {

class Camera : public TransformBase {
 public:
   Camera() {};
   ~Camera() {};

   void Init();

   void Update();

   void Call(UINT num) { buf_->BaindComuputeCBV(num); };

#pragma region Get

   ID3D12Resource *GetBuf() { return buf_->GetResource(); }
   const system::SCamera &GetForGpu() const { return forGpu_; }
#pragma endregion

 private:
   void ConvertData();

   Math::Matrix::Mat4x4 PerspectiveFovMatrix2(float fovY, float aspectRatio, float nearClip, float farClip);

   std::shared_ptr<Base::DX::DXBufferResource<system::SCamera>> buf_ = nullptr;

   system::SCamera forGpu_;

   Math::Matrix::Mat4x4 matProj_ = {};
   Math::Matrix::Mat4x4 mtxProjInv_ = {};
   Math::Matrix::Mat4x4 matView_ = {};
   Math::Matrix::Mat4x4 mtxViewInv_ = {};

   Math::Vector::Vec3 dfScale = {1.0f, 1.0f, 1.0f};

   float fov_ = 0.45f;
   float aspectRatio_ = static_cast<float>(CLEYERA::Base::Win::WinApp::GetKWindowWidth() / CLEYERA::Base::Win::WinApp::GetKWindowHeight());

   float nearClip_ = 0.1f;
   float farClip_ = 1000.0f;
};

} // namespace Util
} // namespace CLEYERA

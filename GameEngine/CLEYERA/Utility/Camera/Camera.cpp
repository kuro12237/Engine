#include "Camera.h"

void CLEYERA::Util::Camera::Init() {

   aspectRatio_ = float(1280.0f / 720.0f);

   matProj_ = Math::Matrix::Func::PerspectiveFovMatrix(fov_, aspectRatio_, nearClip_, farClip_);
   this->matView_.Identity();
   this->mat_.Identity();

   SetScale(dfScale);

   buf_ = std::make_shared<Base::DX::DXBufferResource<system::SCamera>>();
   buf_->SetDevice(Base::DX::DXManager::GetInstance()->GetDevice());
   buf_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
}

void CLEYERA::Util::Camera::Update() {

   WorldMatUpdate();

   mtxViewInv_ = mat_;
   matView_ = mat_.Inverse();
   matProj_ = Math::Matrix::Func::PerspectiveFovMatrix(fov_, aspectRatio_, nearClip_, farClip_);
   mtxProjInv_ = matProj_.Inverse();

   ConvertData();

   buf_->Map();
   buf_->SetParam(forGpu_);
   buf_->UnMap();
}

void CLEYERA::Util::Camera::ConvertData() {

   forGpu_.matProj_ = matProj_;
   forGpu_.mtxProjInv_ = mtxProjInv_;
   forGpu_.matView_ = matView_;
   forGpu_.mtxViewInv_ = mtxViewInv_;
   forGpu_.mtxVP_ = Math::Matrix::Func::Multiply(matView_, matProj_);
   forGpu_.orthographic = Math::Matrix::Func::OrthographicMatrix(0, 0, float(1280), float(720), 0.0f, 100.0f);
   Math::Vector::Vec4 pos = {translate_->x, translate_->y, translate_->z, 1.0f};
   forGpu_.cameraPos_ = pos;
}

Math::Matrix::Mat4x4 CLEYERA::Util::Camera::PerspectiveFovMatrix2(float fovY, float aspectRatio, float nearClip, float farClip) {

   Math::Matrix::Mat4x4 result = {};
   float theta = fovY / 2.0f;

   result.m[0][0] = (1.0f / aspectRatio) * Math::Vector::Func::Cot(theta);
   result.m[0][1] = 0;
   result.m[0][2] = 0;
   result.m[0][3] = 0;

   result.m[1][0] = 0;
   result.m[1][1] = Math::Vector::Func::Cot(theta);
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

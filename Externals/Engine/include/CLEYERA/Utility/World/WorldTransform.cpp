#include "WorldTransform.h"

void CLEYERA::Util::WorldTransform::WTCreate(const uint32_t &instanceNum) {

   camera_ = &Manager::CameraManager::GetInstance()->GetCamera().lock()->GetForGpu();

   this->instanceNum_ = &instanceNum;
   mat_.Identity();

   buf_ = std::make_shared<Base::DX::DXBufferResource<Util::system::forWorldMat>>();
   buf_->Init();
   buf_->SetDevice(Base::DX::DXManager::GetInstance()->GetDevice());
   buf_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);

}

void CLEYERA::Util::WorldTransform::ConvertMat() {
   camera_ = &Manager::CameraManager::GetInstance()->GetCamera().lock()->GetForGpu();

   forGpuWorldMat_.worldMat_ = mat_;

   Math::Vector::Vec3 pos = GetWorldPos();
   forGpuWorldMat_.worldPos_ = Math::Vector::Vec4(pos.x, pos.y, pos.z, 1.0f);

   //forGpuWorldMat_.worldMatInv_ = forGpuWorldMat_.worldMat_.Inverse();
   if (camera_) {

      forGpuWorldMat_.WPV_ = Math::Matrix::Func::Multiply(forGpuWorldMat_.worldMat_, camera_->mtxVP_);
   }
   SetWorldTransfar();
}

void CLEYERA::Util::WorldTransform::SetWorldTransfar() {

   buf_->Map();
   buf_->SetParam(forGpuWorldMat_);

   buf_->Update();
}

void CLEYERA::Util::WorldTransform::BindWT(UINT num) {
  ConvertMat();
    SetWorldTransfar();
    buf_->GraphicsCommand(num); }

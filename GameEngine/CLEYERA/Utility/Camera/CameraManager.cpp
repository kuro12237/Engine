#include "CameraManager.h"

CLEYERA::Manager::CameraManager *CLEYERA::Manager::CameraManager::GetInstance() {

   static CameraManager instance;
   return &instance;
}

void CLEYERA::Manager::CameraManager::Init() {
   dxManager_ = Base::DX::DXManager::GetInstance();

   commandManager_ = Base::DX::DXCommandManager::GetInstace();
}

void CLEYERA::Manager::CameraManager::Update() {
   if (camera_.expired()) {
      // カメラをセットしていない
      assert(false);
   }

   auto camera = camera_.lock();
   camera->Update();
}

void CLEYERA::Manager::CameraManager::BindCommand(UINT num) {
   if (camera_.expired()) {
      // カメラをセットしていない
      assert(false);
   }

   commandManager_->GraphicsCommandCall(num, camera_.lock()->GetBuf());
}

void CLEYERA::Manager::CameraManager::BindComputeCommand(UINT num) { camera_.lock()->Call(num); }

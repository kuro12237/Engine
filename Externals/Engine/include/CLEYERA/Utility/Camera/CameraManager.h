#pragma once
#include "Camera.h"

namespace CLEYERA {
namespace Manager {

/// <summary>
/// カメラ管理クラス
/// </summary>
class CameraManager {
 public:
   static CameraManager *GetInstance();

   void Init();

   void Update();

   /// <summary>
   /// コマンドをセット
   /// </summary>
   /// <param name="num"></param>
   void BindCommand(UINT num);

   void BindComputeCommand(UINT num);

#pragma region Set
   void SetCamera(std::weak_ptr<Util::Camera> c) { camera_ = c; }
#pragma endregion

#pragma region Get
   std::weak_ptr<Util::Camera> GetCamera() { return camera_; }
#pragma endregion

 private:
   std::weak_ptr<Util::Camera> camera_;

   Base::DX::DXManager *dxManager_ = nullptr;
   Base::DX::DXCommandManager *commandManager_ = nullptr;
#pragma region Single

   CameraManager() = default;
   ~CameraManager() = default;
   CameraManager(const CameraManager &) = delete;
   CameraManager &operator=(const CameraManager &) = delete;

#pragma endregion
};

} // namespace Manager
} // namespace CLEYERA
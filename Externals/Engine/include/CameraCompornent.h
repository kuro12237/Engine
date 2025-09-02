#pragma once

#include "../Utility/Camera/Camera.h"
#include "../Utility/Camera/CameraManager.h"
#include "../Utility/Input/InputManager.h"
#include "Utility/ColliderSystem/ColliderSystem.h"

#include "JsonCompornent.h"

namespace CLEYERA {

namespace Component {

/// <summary>
/// カメラ
/// </summary>
class CameraCompornent {
 public:
   CameraCompornent();
   virtual ~CameraCompornent() {};

   virtual void Init() = 0;

   virtual void Update() = 0;

   virtual void ImGuiUpdate();

   std::weak_ptr<Util::Camera> GetCamera() { return camera_; };

   
   template <typename T> T GetValue(const std::string &name) { return jsonSystem_->GetValue<T>(name); }
   template <typename T> void SetValue(const std::string &name, T t) { jsonSystem_->SetValue<T>(name, t); }

 private:
   CLEYERA::Manager::CameraManager *cameraManager_ = nullptr;

 protected:
   /// <summary>
   /// jsonの作成
   /// </summary>
   void CreateJsonSystem(const std::string &fileGroupName);

   void SetImGuiFunc(std::function<void(CameraCompornent &camera)> func) { imGuiFunc_ = func; }

   std::string name_ = "";

   Manager::ColliderSystem *colliderSystem_ = nullptr;
   Manager::InputManager *inputManager_ = nullptr;

   std::function<void(CameraCompornent& camera)> imGuiFunc_ = nullptr;

   /// <summary>
   /// 切り替えたいときこの関数を呼び出す
   /// </summary>
   void CameraChange();

   std::shared_ptr<CLEYERA::Util::Camera> camera_ = nullptr;

   // jsonのシステム
   std::shared_ptr<Component::JsonCompornent> jsonSystem_ = nullptr;

   Math::Vector::Vec3 rotate_ = {};
   Math::Vector::Vec3 degreeRotate_ = {};
   Math::Vector::Vec3 translate_ = {0.0f, 0.0f, -16.0f};
};

} // namespace Component
} // namespace CLEYERA
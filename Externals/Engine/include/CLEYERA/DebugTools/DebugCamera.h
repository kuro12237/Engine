#pragma once
#include"../Utility/Camera/CameraManager.h"
#include "../Utility/Camera/Camera.h"

namespace CLEYERA {

namespace DebugTools {

class DebugCamera {
 public:
   DebugCamera() {};
   ~DebugCamera() {};

   void Init();

   void Update();

   void ImGuiUpdate();

 private:
   std::shared_ptr<CLEYERA::Util::Camera> camera_ = nullptr;

   Math::Vector::Vec3 rotate_ = {};
   Math::Vector::Vec3 translate_ = {0.0f, 0.0f, -16.0f};
};


}
} // namespace CLEYERA

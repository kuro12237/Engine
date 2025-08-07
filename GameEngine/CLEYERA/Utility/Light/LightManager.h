#pragma once
#include "DIrectionLight.h"

namespace CLEYERA {

namespace Manager {

class LightManager {
 public:
   static LightManager *GetInstance() {
      static LightManager instance;
      return &instance;
   }

   void Init();

   void Update();

   void Finalize() { directionLight_.reset(); }

   void ImGuiUpdate();

   void DirectionLightCommandBind(UINT num) { directionLight_->CommandBind(num); }

 private:
   std::shared_ptr<DirectionLight> directionLight_;

#pragma region Single

   LightManager() = default;
   ~LightManager() = default;
   LightManager(const LightManager &) = delete;
   LightManager &operator=(const LightManager &) = delete;

#pragma endregion
};

} // namespace Manager
} // namespace CLEYERA
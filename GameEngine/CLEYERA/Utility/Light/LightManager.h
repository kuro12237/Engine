#pragma once
#include "../../Compornent/PointLightComponent.h"
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

  void Finalize() {
    directionLight_.reset();
    pointData_.reset();
  }

  void ImGuiUpdate();

  void DirectionLightCommandBind(UINT num) { directionLight_->CommandBind(num); }
  void PointLightCommandBind(UINT num);
  void SetPointLightData(const Component::System::PointLightForGPU *light) {
    pointLights_[lightNum_] = light;
    lightNum_++;
  };

private:
  std::shared_ptr<DirectionLight> directionLight_;
  std::shared_ptr<Base::DX::DXBufferResource<Component::System::PointLightForGPU>> pointData_;
  std::vector<const Component::System::PointLightForGPU*> pointLights_;

  int lightNum_ =0;
#pragma region Single

  LightManager() = default;
  ~LightManager() = default;
  LightManager(const LightManager &) = delete;
  LightManager &operator=(const LightManager &) = delete;

#pragma endregion
};

} // namespace Manager
} // namespace CLEYERA
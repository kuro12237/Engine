#include "PointLightComponent.h"
#include "Utility/Light/LightManager.h"

namespace CLEYERA {

namespace Component {

void PointLightComponent::Create() { Manager::LightManager::GetInstance()->SetPointLightData(&gpuData_); }

void PointLightComponent::TransfarGPU() {
  gpuData_.intensity = intensity_;
  gpuData_.decay = decay_;
  gpuData_.pos_ = pos_;
  gpuData_.rad = rad_;
  gpuData_.color_ = color_;
}

} // namespace Component

} // namespace CLEYERA

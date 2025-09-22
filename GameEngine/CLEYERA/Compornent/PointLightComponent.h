#pragma once
#include "pch/Pch.h"

namespace CLEYERA {

namespace Manager {
class LightManager;
}

namespace Component {

namespace System {

struct PointLightForGPU {

  Math::Vector::Vec3 pos_;
  float rad;
  float intensity;
  float decay;
};
} // namespace System


/// <summary>
/// ポイントライト
/// </summary>
class PointLightComponent {
public:
  PointLightComponent() {};
  virtual ~PointLightComponent() {};

  virtual void Init() = 0;
  virtual void Update() = 0;

private:


  System::PointLightForGPU gpuData_;

protected:
  void Create();
  void TransfarGPU();

  Math::Vector::Vec3 pos_ = {};
  float rad_ = 1.0f;
  float intensity_ = 1.0f;
  float decay_ = 1.0f;
};

} // namespace Component
} // namespace CLEYERA
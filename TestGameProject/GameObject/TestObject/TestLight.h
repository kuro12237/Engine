#pragma once
#include "CLEYERA.h"
#include"Compornent/PointLightComponent.h"

class TestPointLight : public CLEYERA::Component::PointLightComponent {
public:
  TestPointLight() {};
  ~TestPointLight() {};

  void Init() override;
  void Update() override;

private:

};
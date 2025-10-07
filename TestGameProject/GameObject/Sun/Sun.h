#pragma once
#include"CLEYERA.h"

#include"Compornent/PointLightComponent.h"

class Sun :public CLEYERA::Component::PointLightComponent{
public:
  Sun() {};
  ~Sun() {};

  void Init() override;

  void Update() override;

private:
};

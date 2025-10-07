#pragma once
#include"CLEYERA.h"

class TestCamera:public CLEYERA::Component::CameraCompornent {
public:
  TestCamera() {};
  ~TestCamera() {};

  void Init()override;
  void Update() override;

private:

	Math::Vector::Vec3 rot_={};
};

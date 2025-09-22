#pragma once
#include "CLEYERA.h"

class TestTerrain : public CLEYERA::Component::ObjectComponent {
public:
  TestTerrain() {};
  ~TestTerrain() {};

  void Init() override;

  void Update() override;


  void SetPos(const Math::Vector::Vec3 &pos) { translate_ = pos; }

private:
  float lifeTime_ = 0.0f;
  float lifeMax_ = 2.0f;
};
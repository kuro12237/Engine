#pragma once
#include "CLEYERA.h"

class TestPointLight : public CLEYERA::Component::PointLightComponent {
public:
  TestPointLight() {};
  ~TestPointLight() {};

  void Init() override;
  void Update() override;

private:
  float Rand01() {
    static std::mt19937 mt{std::random_device{}()};
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(mt);
  }

  Math::Vector::Vec2 velo_ = {};
  float moveRad_ = 8.0f;
  float flame_ = 0.0f;
  float angle_ = 0.0f;
  float anglerSpeed_ = 0.1f;
  Math::Vector::Vec2 center_ = {};
};

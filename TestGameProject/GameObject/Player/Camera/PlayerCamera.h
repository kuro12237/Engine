#pragma once
#include "CLEYERA.h"

class PlayerCamera : public CLEYERA::Component::CameraCompornent {
public:
  PlayerCamera() {};
  ~PlayerCamera() {};

  void Init() override;
  void Update() override;

  void SetPlayerPos(const Math::Vector::Vec3 *pos) { p_playerPos_ = pos; }

private:
  const Math::Vector::Vec3 *p_playerPos_ = nullptr;
  Math::Vector::Vec3 offset_ = {0.0f, 2.0f, -32.0f};

};

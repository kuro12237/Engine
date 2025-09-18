#pragma once
#include "CLEYERA.h"

class SkySphere : public CLEYERA::Component::ObjectComponent {
public:
  SkySphere() {};
  ~SkySphere() {};

  void Init() override;

  void Update() override;

  /// <summary>
  /// 衝突時コールバック//これは固定
  /// </summary>
  void OnCollision(std::weak_ptr<ObjectComponent> other);

  void SetPos(const Math::Vector::Vec3 &pos) { translate_ = pos; }

private:
  float lifeTime_ = 0.0f;
  float lifeMax_ = 2.0f;
};

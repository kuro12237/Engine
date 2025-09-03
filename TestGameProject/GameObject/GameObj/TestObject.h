#pragma once
#include "CLEYERA.h"

class TestObj : public CLEYERA::Component::ObjectComponent {
public:
  TestObj() {};
  ~TestObj() {};

  void Init() override;

  void Update() override;

  /// <summary>
  /// 衝突時コールバック//これは固定
  /// </summary>
  void OnCollision(std::weak_ptr<ObjectComponent> other);

private:
};

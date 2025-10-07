#pragma once
#include "CLEYERA.h"

class TestObj : public CLEYERA::Component::ObjectComponent {
public:
  TestObj() {};
  ~TestObj() {};

  void Init() override;

  void Update() override;


private:
};
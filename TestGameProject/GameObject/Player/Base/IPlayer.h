#pragma once
#include "CLEYERA.h"

class IPlayer : public CLEYERA::Component::ObjectComponent {
public:
  IPlayer() {};
  virtual ~IPlayer() {};

  virtual void Init() = 0;

  virtual void Update() = 0;

private:
};

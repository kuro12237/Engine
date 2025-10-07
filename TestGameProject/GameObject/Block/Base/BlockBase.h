#pragma once
#include "CLEYERA.h"

class BlockBase : public CLEYERA::Component::ObjectComponent {
public:
  BlockBase() {};
  virtual ~BlockBase() {};

  virtual void Init() = 0;
  virtual void Update() = 0;

protected:
  void CreateData();
  virtual void OnCollision(std::weak_ptr<ObjectComponent> other) {};

private:
};

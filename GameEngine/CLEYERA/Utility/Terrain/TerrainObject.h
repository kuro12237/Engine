#pragma once
#include"Compornent/ObjectCompornent.h"


class TerrainObject:public CLEYERA::Component::ObjectComponent {
public:
  TerrainObject() {};
  ~TerrainObject() {};

  void Init() override;

  void Update() override;

private:
};
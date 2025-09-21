#pragma once
#include "InstancingBase.h"

namespace CLEYERA {

namespace Model3d {

class InstancingMaterial
    : public InstancingBase<Model3d::Material::ColorMaterialData> {
public:
  InstancingMaterial() {};
  ~InstancingMaterial() {};

  void Init(uint32_t max = 1) override;

  void Update() override;

private:
};

} // namespace Model3d
} // namespace CLEYERA
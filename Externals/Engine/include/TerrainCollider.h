#pragma once

#include "Collider.h"
#include "SCollider.h"

namespace CLEYERA {

namespace Util {

namespace Collider {

class TerrainCollider : public Collider {
 public:
   TerrainCollider() {};
   ~TerrainCollider() {};

   void ColliderImGuiUpdate() override;

   void HitCallFunc(const Collider &other) override {};

   void Create() override;

   void Update() override;

   void ColliderImGuiUpdate(const std::string &name) override;

 private:
};

} // namespace Collider
} // namespace Util
} // namespace CLEYERA
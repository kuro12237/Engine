#include "Collider.h"

bool CLEYERA::Util::Collider::Collider::HitCall(std::weak_ptr<Component::ObjectComponent> other) {

   for (size_t i = 0; i < colors_.size(); i++) {
      colors_[i] = {0.0f, 1.0f, 0.0f, 1.0f};
   }

   isHit_ = true;
   if (HitCallFunc) {
     HitCallFunc(other);
   }
   return true;
}

void CLEYERA::Util::Collider::Collider::MortonUpdate() {



}



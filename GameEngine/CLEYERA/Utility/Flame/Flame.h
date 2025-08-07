#pragma once
#include "../../pch/Pch.h"

namespace CLEYERA {
namespace Util {

class Flame {
 public:
   static Flame *GetInstance() {
      static Flame instance;
      return &instance;
   }

   void Init();

   void Update();

   void ImGuiUpdate();

   float GetFlameLate() { return flamelate_; }
 private:
   std::chrono::steady_clock::time_point reference_ = {};

   float fps_ = 0.0f;
   float flamelate_ = 0.0f;

#pragma region Singleton
   Flame() = default;
   ~Flame() = default;
   Flame(const Flame &) = delete;
   Flame &operator=(const Flame &) = delete;

#pragma endregion
};

} // namespace Util
} // namespace CLEYERA
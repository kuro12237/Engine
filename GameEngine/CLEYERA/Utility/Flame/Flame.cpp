#include "Flame.h"

using namespace std::chrono;

void CLEYERA::Util::Flame::Init() { reference_ = std::chrono::steady_clock::now(); }

void CLEYERA::Util::Flame::Update() {

   const microseconds kMinTime(uint64_t(1000000.0f / 60.0f));

   const microseconds kMinCheckTime(uint64_t(1000000.0f / 65.0f));

   steady_clock::time_point now = steady_clock::now();

   microseconds elapsed = duration_cast<microseconds>(now - reference_);
   fps_ = 1000000.0f / static_cast<float>(elapsed.count());
   // 1/60
   if (elapsed < kMinTime) {

      while (steady_clock::now() - reference_ < kMinCheckTime) {
         std::this_thread::sleep_for(microseconds(1));
      }
   }
   reference_ = steady_clock::now();
}

void CLEYERA::Util::Flame::ImGuiUpdate() { ImGui::Text("fps::%f", fps_);

}

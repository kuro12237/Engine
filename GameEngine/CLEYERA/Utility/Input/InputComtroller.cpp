#include "InputComtroller.h"

void CLEYERA::Util::InputController::Init() {}

void CLEYERA::Util::InputController::Begin() {

   preJoyState_ = joyState_;
   XInputGetState(0, &joyState_);
}

Math::Vector::Vec2 CLEYERA::Util::InputController::GetJoyLStickPos(const float &mode) {

   float deadzone = 0.1f;

   Math::Vector::Vec2 joyPos(joyState_.Gamepad.sThumbLX / mode, joyState_.Gamepad.sThumbLY / mode);

   if (std::abs(joyPos.x) > deadzone || std::abs(joyPos.y) > deadzone) {
      return joyPos;
   }
   return {};
}

Math::Vector::Vec2 CLEYERA::Util::InputController::GetJoyRStickPos(const float &mode) {

   float deadzone = 0.1f;
   Math::Vector::Vec2 joyPos(joyState_.Gamepad.sThumbRX / mode, joyState_.Gamepad.sThumbRY / mode);

   if (std::abs(joyPos.x) > deadzone || std::abs(joyPos.y) > deadzone) {
      return joyPos;
   }

   return {};
}

bool CLEYERA::Util::InputController::PushBottonPressed(uint32_t GameBotton) {
   bool preFlag = false;

   if (preJoyState_.Gamepad.wButtons & GameBotton) {
      preFlag = true;
   }

   if (!preFlag && joyState_.Gamepad.wButtons & GameBotton) {
      return true;
   }

   return false;
}

bool CLEYERA::Util::InputController::PushBotton(uint32_t GameBotton) {

   if (joyState_.Gamepad.wButtons & GameBotton) {
      return true;
   }
   return false;
}

uint8_t CLEYERA::Util::InputController::GetRightTriggerValue() { return joyState_.Gamepad.bRightTrigger; }

bool CLEYERA::Util::InputController::IsRightTriggerPressed(uint8_t threshold) {
   // 右トリガーの押し込み具合が閾値を超えているかを判定
   return joyState_.Gamepad.bRightTrigger > threshold;
}

uint8_t CLEYERA::Util::InputController::GetLeftTriggerValue() { return joyState_.Gamepad.bLeftTrigger; }

bool CLEYERA::Util::InputController::IsLeftTriggerPressed(uint8_t threshold) {
   // 左トリガーの押し込み具合が閾値を超えているかを判定
   return joyState_.Gamepad.bLeftTrigger > threshold;
}

bool CLEYERA::Util::InputController::IsLJoystickActive() {

   float joystickThreshold_ = 0.2f;
   Math::Vector::Vec2 Ljoy = GetJoyLStickPos();
   if (std::abs(Ljoy.x) > joystickThreshold_ || std::abs(Ljoy.y) > joystickThreshold_) {

      return true;
   }
   return false;
}

bool CLEYERA::Util::InputController::IsRJoystickActive() {
   float joystickThreshold_ = 0.2f;
   Math::Vector::Vec2 Rjoy = GetJoyRStickPos();
   if (std::abs(Rjoy.x) > joystickThreshold_ || std::abs(Rjoy.y) > joystickThreshold_) {

      return true;
   }
   return false;
}
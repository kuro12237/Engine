#include "InputKeybord.h"

void CLEYERA::Util::InputKeyBord::Init() {

   // InputDevice
   HRESULT hr = DirectInput8Create(CLEYERA::Base::Win::WinApp::GetInstance()->GetWC().hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&directInput_, nullptr);

   assert(SUCCEEDED(hr));
   directInput_->CreateDevice(GUID_SysKeyboard, &keyboard_, NULL);
   assert(SUCCEEDED(hr));
   hr = keyboard_->SetDataFormat(&c_dfDIKeyboard);
   assert(SUCCEEDED(hr));
   //
   hr = keyboard_->SetCooperativeLevel(Base::Win::WinApp::GetInstance()->GetHWND(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
   assert(SUCCEEDED(hr));
}

void CLEYERA::Util::InputKeyBord::Begin() {
   memcpy(preKeys, keys, 256);
   keyboard_->Acquire();
   keyboard_->GetDeviceState(sizeof(keys), keys);
}

bool CLEYERA::Util::InputKeyBord::PushKey(uint8_t keyNum) {

   if (keys[keyNum] == 0x80) {
      return true;
   }
   return false;
}

bool CLEYERA::Util::InputKeyBord::PushKeyPressed(uint32_t keyNum) {
   if (keys[keyNum] == 0x80 && preKeys[keyNum] == 0x00) {
      return true;
   }
   return false;
}

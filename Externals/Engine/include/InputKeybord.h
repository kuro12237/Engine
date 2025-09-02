#pragma once
#include "../../WIn/WinApp.h"
#include "../../pch/Pch.h"

namespace CLEYERA {

namespace Util {

class InputKeyBord {
 public:
   InputKeyBord() {};
   ~InputKeyBord() {};

   void Init();

   void Begin();

   /// <summary>
   /// 押されているか
   /// </summary>
   /// <param name="keyNum"></param>
   /// <returns></returns>
   bool PushKey(uint8_t keyNum);

   /// <summary>
   /// 一瞬　押したか
   /// </summary>
   bool PushKeyPressed(uint32_t keyNum);

 private:
   ComPtr<IDirectInputDevice8> keyboard_ = nullptr;
   ComPtr<IDirectInput8> directInput_ = nullptr;

   BYTE keys[256] = {};
   BYTE preKeys[256] = {};
};

} // namespace Util
} // namespace CLEYERA
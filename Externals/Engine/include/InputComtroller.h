#pragma once
#include "pch/Pch.h"

namespace CLEYERA {

namespace Util {

class InputController {
 public:
   InputController() {};
   ~InputController() {};

   void Init();

   void Begin();

   /// <summary>
   /// Lstic
   /// </summary>
   /// <param name="mode"></param>
   /// <returns></returns>
   Math::Vector::Vec2 GetJoyLStickPos(const float &mode = SHRT_MAX);

   /// <summary>
   /// Rstic
   /// </summary>
   /// <param name="mode"></param>
   /// <returns></returns>
   Math::Vector::Vec2 GetJoyRStickPos(const float &mode = SHRT_MAX);

   /// <summary>
   /// ボタンのトリガー
   /// </summary>
   /// <param name="GameBotton"></param>
   /// <returns></returns>
   bool PushBottonPressed(uint32_t GameBotton);

   /// <summary>
   /// ボタン押し続けてる
   /// </summary>
   /// <param name="GameBotton"></param>
   /// <returns></returns>
   bool PushBotton(uint32_t GameBotton);

   /// <summary>
   /// RTの押し込み具合を取得
   /// </summary>
   /// <returns>押し込み具合（0～255）</returns>
   uint8_t GetRightTriggerValue();

   /// <summary>
   /// RTが押し込まれているかを判定
   /// </summary>
   /// <param name="threshold">押し込み判定の閾値</param>
   /// <returns>押し込まれている場合はtrue</returns>
   bool IsRightTriggerPressed(uint8_t threshold = 30);

   /// <summary>
   /// LTの押し込み具合を取得
   /// </summary>
   /// <returns>押し込み具合（0～255）</returns>
   uint8_t GetLeftTriggerValue();

   /// <summary>
   /// LTが押し込まれているかを判定
   /// </summary>
   /// <param name="threshold">押し込み判定の閾値</param>
   /// <returns>押し込まれている場合はtrue</returns>
   bool IsLeftTriggerPressed(uint8_t threshold = 30);

   bool IsLJoystickActive();

   bool IsRJoystickActive();

 private:
   XINPUT_STATE joyState_{};
   XINPUT_STATE preJoyState_{};
};

} // namespace Util
} // namespace CLEYERA
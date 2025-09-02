#pragma once
#include "../../pch/Pch.h"

#include "InputComtroller.h"
#include "InputKeybord.h"

namespace CLEYERA {

namespace Manager {

class InputManager {
 public:
   static InputManager *GetInstance() {
      static InputManager instance;
      return &instance;
   };

   void Init();
   void Finalize();

   void Begin();

   /// <summary>
   /// 押されているか
   /// </summary>
   /// <param name="keyNum"></param>
   /// <returns></returns>
   bool PushKey(uint8_t keyNum) { return keyBord_->PushKey(keyNum); };

   /// <summary>
   /// 一瞬　押したか
   /// </summary>
   bool PushKeyPressed(uint32_t keyNum) { return keyBord_->PushKeyPressed(keyNum); };

   /// <summary>
   /// コントローラのRPos
   /// </summary>
   /// <returns></returns>
   Math::Vector::Vec2 JoyRPos() { return controller_->GetJoyRStickPos(); }

   /// <summary>
   /// コントローラのLPos
   /// </summary>
   /// <returns></returns>
   Math::Vector::Vec2 JoyLPos() { return controller_->GetJoyLStickPos(); }

   /// <summary>
   /// ボタンのトリガー
   /// </summary>
   /// <param name="GameBotton"></param>
   /// <returns></returns>
   bool PushBottonPressed(uint32_t GameBotton) { return controller_->PushBottonPressed(GameBotton); }

   /// <summary>
   /// ボタン押し続けてる
   /// </summary>
   /// <param name="GameBotton"></param>
   /// <returns></returns>
   bool PushBotton(uint32_t GameBotton) { return controller_->PushBotton(GameBotton); };

    /// <summary>
   /// LTの押し込み具合を取得
   /// </summary>
   /// <returns>押し込み具合（0～255）</returns>
   uint8_t GetLeftTriggerValue() { return controller_->GetLeftTriggerValue(); }

   /// <summary>
   /// LTが押し込まれているかを判定
   /// </summary>
   /// <param name="threshold">押し込み判定の閾値</param>
   /// <returns>押し込まれている場合はtrue</returns>
   bool IsLeftTriggerPressed(uint8_t threshold = 30) { return controller_->IsLeftTriggerPressed(threshold); }

   /// <summary>
   /// RTの押し込み具合を取得
   /// </summary>
   /// <returns>押し込み具合（0～255）</returns>
   uint8_t GetRightTriggerValue() { return controller_->GetRightTriggerValue(); }

   /// <summary>
   /// RTが押し込まれているかを判定
   /// </summary>
   /// <param name="threshold">押し込み判定の閾値</param>
   /// <returns>押し込まれている場合はtrue</returns>
   bool IsRightTriggerPressed(uint8_t threshold = 30) { return controller_->IsRightTriggerPressed(threshold); }

   bool IsLJoystickActive() { return controller_->IsLJoystickActive(); }
   bool IsRJoystickActive() { return controller_->IsRJoystickActive(); }

 private:
   std::unique_ptr<Util::InputKeyBord> keyBord_ = nullptr;
   std::unique_ptr<Util::InputController> controller_ = nullptr;
#pragma region Singleton

   InputManager() = default;
   ~InputManager() = default;
   InputManager(const InputManager &) = delete;
   InputManager &operator=(const InputManager &) = delete;

#pragma endregion
};

} // namespace Manager

} // namespace CLEYERA
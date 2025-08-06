#pragma once
#include "../SystemLogManager/ISystemObserver.h"
#include"../pch/Pch.h"


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace CLEYERA {
namespace Base {
namespace Win {

class WinApp {
public:
  static WinApp *GetInstance();

  /// <summary>
  ///
  /// </summary>
  void Create();

  /// <summary>
  ///
  /// </summary>
  void Finalize();

  /// <summary>
  ///
  /// </summary>
  /// <returns></returns>
  bool WinMsg();

#pragma region Get

  static int32_t GetKWindowWidth() { return kWindowWidth; }
  static int32_t GetKWindowHeight() { return kWindowHeight; }

  HWND GetHWND() { return hwnd_; }
  WNDCLASS GetWC() { return wc_; }
#pragma endregion

private:
  /// <summary>
  ///
  /// </summary>
  static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam,
                                     LPARAM lparam);

  static const int32_t kWindowWidth = 1280;
  static const int32_t kWindowHeight = 720;

  MSG msg{};
  WNDCLASS wc_{};
  HWND hwnd_ = {};
  HWND DebugHwnd_{};

  WinApp() = default;
  ~WinApp() = default;
  WinApp(const WinApp &) = delete;
  const WinApp &operator=(const WinApp &) = delete;
};
} // namespace Win
} // namespace Base
} // namespace CLEYERA
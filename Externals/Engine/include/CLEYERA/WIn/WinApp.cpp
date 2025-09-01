#include "WinApp.h"

using namespace CLEYERA::Base::Win;

WinApp *CLEYERA::Base::Win::WinApp::GetInstance() {
   static WinApp instance;
   return &instance;
}

void WinApp::Create() {
   wc_.lpfnWndProc = WinApp::WindowProc;
   wc_.lpszClassName = L"CLEYERA";
   wc_.hInstance = GetModuleHandle(nullptr);
   wc_.hCursor = LoadCursor(nullptr, IDC_ARROW);
   RegisterClass(&wc_);

   RECT wrc = {0, 0, kWindowWidth, kWindowHeight};
   AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

   hwnd_ = CreateWindow(wc_.lpszClassName, L"CLEYERA", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, wrc.right - wrc.left, wrc.bottom - wrc.top, nullptr, nullptr, wc_.hInstance, nullptr);
   HFONT hFont = CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
   SendMessage(hwnd_, WM_SETFONT, (WPARAM)hFont, TRUE);

   ShowWindow(hwnd_, SW_SHOW);

   timeBeginPeriod(1);
}

void CLEYERA::Base::Win::WinApp::Finalize() { CloseWindow(hwnd_); }

bool CLEYERA::Base::Win::WinApp::WinMsg() {

   if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }

   if (msg.message != WM_QUIT) {
      return true;
   }

   return false;
}

LRESULT CLEYERA::Base::Win::WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

  
   if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
      return true;
   }
   switch (msg) {
   case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
   }
   return DefWindowProc(hwnd, msg, wparam, lparam);
}

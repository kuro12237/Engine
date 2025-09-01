#include "CLEYERA.h"
#pragma comment(lib, "math.lib")
#pragma comment(lib, "imgui.lib")
#pragma comment(lib, "DirectXTex.lib")

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

  std::unique_ptr<Engine> engine_ = std::make_unique<Engine>();

  engine_->Init();
  engine_->Run();
  engine_->Finalize();

  return 0;
}
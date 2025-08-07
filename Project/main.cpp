#include "CLEYERA/CLEYERA.h"

/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

  std::unique_ptr<Engine> engine_ = std::make_unique<Engine>();

  engine_->Init();
  engine_->Run();
  engine_->Finalize();

  return 0;
}
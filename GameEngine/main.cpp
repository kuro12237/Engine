#include "CLEYERA.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

  std::unique_ptr<Engine> engine_ = std::make_unique<Engine>();

  engine_->Init();
  engine_->Run();
  engine_->Finalize();

  return 0;
}
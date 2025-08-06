#include "CLEYERA/CLEYERA.h"

/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

  std::unique_ptr<Engine> engine_ = std::make_unique<Engine>();

  engine_->Init();

  while (CLEYERA::Base::Win::WinApp::GetInstance()->WinMsg()) {
    engine_->Begin();

    engine_->PhysiceForcesUpdate();

    engine_->Update();

    engine_->PreDraw();

#ifdef _DEBUG

    engine_->ImGuiUpdate();

#endif // _DEBUG

    engine_->Draw();

    engine_->End();
  }

  engine_->Finalize();

  return 0;
}
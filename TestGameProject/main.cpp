#include "CLEYERA.h"
#pragma comment(lib, "math.lib")
#pragma comment(lib, "imgui.lib")
#pragma comment(lib, "DirectXTex.lib")

#include "GameObject/TestScene.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

  auto scene = CLEYERA::Manager::SceneManager::GetInstance();
  auto win = CLEYERA::Base::Win::WinApp::GetInstance();

  std::unique_ptr<Engine> engine_ = std::make_unique<Engine>();
  engine_->Init();

  scene->RegisterScene<TestScene>("TestScene");
  scene->ChangeScene("TestScene");

  while (win->WinMsg()) {

    engine_->Run();
  }
  engine_->Finalize();

  return 0;
}
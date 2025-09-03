#include "CLEYERA.h"
#pragma comment(lib, "math.lib")
#pragma comment(lib, "imgui.lib")
#pragma comment(lib, "DirectXTex.lib")

#include"GameObject/TestScene.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

  std::unique_ptr<Engine> engine_ = std::make_unique<Engine>();
 
  engine_->Init();

  CLEYERA::Manager::SceneManager::GetInstance()->RegisterScene<TestScene>(
      "TestScene");

  // 地形モデルの設定
  uint32_t modelHandle =
      CLEYERA::Manager::ModelManager::GetInstance()->LoadModel("Resources/Model/Terrain/", "terrain");
  CLEYERA::Manager::Terrain::GetInstance()->ChengeData(modelHandle);

  CLEYERA::Manager::SceneManager::GetInstance()->ChangeScene("TestScene");

  engine_->Run();
  engine_->Finalize();

  return 0;
}
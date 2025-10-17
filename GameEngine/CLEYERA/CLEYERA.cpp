#include "CLEYERA.h"

using namespace CLEYERA::Base::Win;
using namespace CLEYERA::Base::DX;
using namespace CLEYERA::LogManager;
using namespace CLEYERA::Utility;
using namespace CLEYERA::Graphics;

void Engine::Init() {

  systemLogManager_ = std::make_shared<SystemLogManager>();

  winApp_ = WinApp::GetInstance();
  winApp_->Create();

  dxCommon_ = std::make_shared<DXCommon>(VAR_NAME(DXCommon));
  dxCommon_->SetLogManager(systemLogManager_);
  dxCommon_->Create();

  imGuiCommon_ = std::make_shared<ImGuiCommon>();
  imGuiCommon_->Init();

  imGuiManager_ = ImGuiManager::GetInstance();
  imGuiManager_->SetImGuiCommon(imGuiCommon_);

  raytracingManager_ = std::make_shared<RaytracingManager>();
  raytracingManager_->Create();

  shaderCommon_ = std::make_shared<Shader::system::ShaderCommon>();
  shaderCommon_->Init();
  auto shaderManager = Shader::ShaderManager::GetInstance();
  shaderManager->SetCommon(shaderCommon_);

  rasterPiplineCommon_ = std::make_shared<Raster::system::RasterPiplineCommon>();
  rasterPiplineCommon_->Init();

  rasterPiplineManager_ = Raster::RasterPiplineManager::GetInstance();
  rasterPiplineManager_->SetCommon(rasterPiplineCommon_);
  rasterPiplineManager_->Init();

  CLEYERA::Manager::TexManager::GetInstance()->Init();
  modelManager_ = CLEYERA::Manager::ModelManager::GetInstance();
  modelManager_->Init();

  // CLEYERA::Manager::RenderManager::GetInstance()->Init();
  CLEYERA::Manager::CameraManager::GetInstance()->Init();

  debugCamera_ = std::make_shared<CLEYERA::DebugTools::DebugCamera>();
  debugCamera_->Init();

  grid_ = CLEYERA::DebugTools::Grid::GetInstance();
  grid_->Init();

  lightManager_ = CLEYERA::Manager::LightManager::GetInstance();
  lightManager_->Init();

  objectManager_ = CLEYERA::Manager::ObjectManager::GetInstance();
  colliderSystem_ = CLEYERA::Manager::ColliderSystem::GetInstance();

  inputManager_ = CLEYERA::Manager::InputManager::GetInstance();
  inputManager_->Init();

  flame_ = CLEYERA::Util::Flame::GetInstance();
  flame_->Init();

  terrain_ = CLEYERA::Manager::Terrain::GetInstance();
  // terrain_->Init();

  gravityManager_ = CLEYERA::Manager::GravityManager::GetInstance();
  gravityManager_->Init();

  sceneManager_ = CLEYERA::Manager::SceneManager::GetInstance();

  postEffect_ = CLEYERA::Manager::PostEffectManager::GetInstance();
  postEffect_->Init();

  render_ = std::make_unique<CLEYERA::Manager::RenderManager>();
  render_->Init();

  debugWindow_ = std::make_unique<CLEYERA::DebugTools::DebugWindow>();
}

void Engine::Run() {
  Begin();

  sceneManager_->Update();

  PhysiceForcesUpdate();

  for (auto obj : CLEYERA::Manager::ObjectManager::GetInstance()->GetObjects()) {
    for (auto it : obj.second) {
      if (it.second) {

        it.second->TransformUpdate();
      }
    }
  }

  Update();
  std::vector<ID3D12DescriptorHeap *> desc = {CLEYERA::Base::DX::DXDescripterManager::GetInstance()->GetSRV().lock()->GetDescripter()};
  DXCommandManager::GetInstace()->SetDescripterHeap(desc);

  Draw();

  PreDraw();

#ifdef _DEBUG

  debugWindow_->Update();
  ImGuiUpdate();

#endif // _DEBUG

  render_->PostEffectDraw();
  sceneManager_->Draw2d();
  CLEYERA::Utility::ImGuiManager::GetInstance()->Render();
  dxCommon_->PostDraw();

  End();
}

void Engine::ImGuiUpdate() {
  flame_->ImGuiUpdate();
  dxCommon_->ImGuiUpdate();

  lightManager_->ImGuiUpdate();
  // debugCamera_->ImGuiUpdate();

  // grid_->ImGuiUpdate();
  colliderSystem_->ImGuiUpdate();
  objectManager_->ImGuiUpdate();
  sceneManager_->ImGuiUpdate();
}

void Engine::PhysiceForcesUpdate() { gravityManager_->Update(); }

void Engine::Update() {
  CLEYERA::Base::DX::DXCommandManager *commandManager = CLEYERA::Base::DX::DXCommandManager::GetInstace();
  CLEYERA::Base::Win::WinApp *winApp = CLEYERA::Base::Win::WinApp::GetInstance();

  terrain_->Update();
  objectManager_->Update();

  terrain_->CheckObjct();
  colliderSystem_->Update();
  grid_->Update();
  lightManager_->Update();

  debugCamera_->Update();

  CLEYERA::Manager::CameraManager::GetInstance()->Update();
  postEffect_->Update();

  commandManager->SetViewCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());
  commandManager->SetScissorCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());
}

void Engine::Finalize() {

  render_.reset();
  postEffect_->FInalize();
  sceneManager_->Finalize();
  // CLEYERA::Manager::RenderManager::GetInstance()->Clear();
  CLEYERA::Manager::ObjectManager::GetInstance()->Clear();
  inputManager_->Finalize();
  terrain_->Finalize();
  lightManager_->Finalize();
  grid_->Finalize();

  debugCamera_.reset();

  modelManager_->Finalize();

  CLEYERA::Manager::TexManager::GetInstance()->Finalize();
  shaderCommon_.reset();
  rasterPiplineCommon_.reset();

  raytracingManager_.reset();
  imGuiCommon_.reset();
  dxCommon_->Finalize();
  winApp_->Finalize();
}

void Engine::Begin() {
  inputManager_->Begin();
  CLEYERA::Utility::ImGuiManager::GetInstance()->Begin();
}

void Engine::End() {

  flame_->Update();
  dxCommon_->CommandReset();
}

void Engine::PreDraw() { dxCommon_->PreDraw(); }

void Engine::Draw() {

  render_->PreDraw();
  render_->Draw3d();
  render_->PostDraw();

  // grid_->DrawRaster3d();
}
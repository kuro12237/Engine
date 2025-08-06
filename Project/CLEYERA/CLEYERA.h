#pragma once
#include "DX/DXCommon.h"
#include "SystemLogManager/SystemLogManager.h"
#include "WIn/WinApp.h"

#include "Utility/ImGui/ImGuiManager.h"

#include "3d/Model3d.h"

#include "3d/ModelManager/ModelManager.h"

#include "Graphics/RasterPipline/RasterPiplineManager.h"
#include "Graphics/ShaderManager/ShaderManager.h"

#include "Graphics/RaytracingManager/RaytracingManager.h"
#include "Graphics/TexManager/TexManager.h"

#include "Utility/Camera/CameraManager.h"
#include "Utility/Light/LightManager.h"
#include "Utility/RenderManager/RenderManager.h"

#include "DebugTools/DebugCamera.h"
#include "DebugTools/Grid.h"

#include "Utility/ColliderSystem/ColliderSystem.h"
#include "Utility/FileLoader/FileLoader.h"
#include "Utility/Flame/Flame.h"
#include "Utility/Input/InputManager.h"
#include "Utility/Object/ObjectManager.h"
#include "Utility/PhysicsForces/GravityManager.h"
#include "Utility/Terrain/Terrain.h"

#include "Compornent/CameraCompornent.h"
#include "Compornent/ManagerCompornent.h"
#include "Compornent/ObjectCompornent.h"
#include "Compornent/SpriteComponent.h"

class Engine {
public:
  Engine() {};
  ~Engine() {};

  void Init();

  void ImGuiUpdate();

  void PhysiceForcesUpdate();

  void Update();

  void Finalize();

  void Begin();

  void End();

  void PreDraw();

  void Draw();

#pragma region Get

  std::weak_ptr<CLEYERA::Graphics::RaytracingManager> GetRaytracingManager() {
    return raytracingManager_;
  }
#pragma endregion

private:
  CLEYERA::Base::Win::WinApp *winApp_ = nullptr;
  CLEYERA::Utility::ImGuiManager *imGuiManager_ = nullptr;
  CLEYERA::Manager::ModelManager *modelManager_ = nullptr;
  CLEYERA::Graphics::Raster::RasterPiplineManager *rasterPiplineManager_ = nullptr;
  CLEYERA::DebugTools::Grid *grid_ = nullptr;
  CLEYERA::Manager::LightManager *lightManager_ = nullptr;
  CLEYERA::Manager::ObjectManager *objectManager_ = nullptr;
  CLEYERA::Manager::ColliderSystem *colliderSystem_ = nullptr;
  CLEYERA::Manager::Terrain *terrain_ = nullptr;
  CLEYERA::Manager::InputManager *inputManager_ = nullptr;
  CLEYERA::Manager::GravityManager *gravityManager_ = nullptr;

  CLEYERA::Util::Flame *flame_ = nullptr;

  std::shared_ptr<CLEYERA::DebugTools::DebugCamera> debugCamera_ = nullptr;

  std::shared_ptr<CLEYERA::Graphics::RaytracingManager> raytracingManager_ = nullptr;

  std::shared_ptr<CLEYERA::LogManager::SystemLogManager> systemLogManager_ = nullptr;

  std::shared_ptr<CLEYERA::Graphics::Raster::system::RasterPiplineCommon> rasterPiplineCommon_ =
      nullptr;
  std::shared_ptr<CLEYERA::Graphics::Shader::system::ShaderCommon> shaderCommon_ = nullptr;

  std::shared_ptr<CLEYERA::Base::DX::DXCommon> dxCommon_ = nullptr;
  std::shared_ptr<CLEYERA::Utility::ImGuiCommon> imGuiCommon_ = nullptr;
};

#pragma once
#include "../Graphics/RasterPipline/RasterEnum.h"
#include "../Graphics/TexManager/TexManager.h"
#include "../Utility/Light/LightManager.h"
#include "../Utility/TransformBase/TransformBase.h"
#include "../Utility/World/WorldTransform.h"
#include "ModelManager/ModelManager.h"

#include "Material/BaseMaterial3d.h"
#include "Material/MaterialEnum.h"
#include"Material/ColorMaterial3d.h"

namespace CLEYERA {

namespace Model3d {

/// <summary>
/// ゲームオブジェクト
/// </summary>
class Game3dObject : public CLEYERA::Util::WorldTransform {
public:
  Game3dObject() {};
  ~Game3dObject() {};

  void Create(uint32_t handle);

  void Update();

  void DrawRaster3d();

  void ImGuiUpdate();

  void ChangeModel(uint32_t modelHandle);

  template <typename T> void ChangeMaterialMode();

#pragma region Get
  std::weak_ptr<Model> GetModel() { return model_; }
  const Graphics::RasterPipline_Mode3d &GetRasterMode() const {
    return rasterMode_;
  }
  Material::ColorMaterialData &ColorData() { return colors_; }
#pragma endregion

#pragma region Set
  void SetTexHandle(uint32_t handle) { texHandle_ = handle; }
  void SetName(const std::string &name) { name_ = &name; }
#pragma endregion

private:
  using MaterialMode = Material::MaterialMode;

  const std::string *name_ = nullptr;

  Graphics::RasterPipline_Mode3d rasterMode_ =
      Graphics::RasterPipline_Mode3d::DF_MODEL3d;

  Manager::LightManager *lightManager = nullptr;
  Manager::CameraManager *cameraManager_ = nullptr;
  Manager::ModelManager *modelManager_ = nullptr;
  Manager::TexManager *texManager_ = nullptr;

  Base::DX::DXCommandManager *commandManager_ = nullptr;

  std::shared_ptr<Model> model_ = nullptr;
  std::unique_ptr<IMaterial> material_ = nullptr;

  CLEYERA::Model3d::Material::ColorMaterialData colors_ = {};

  uint32_t modelHandle_ = 0;
  uint32_t texHandle_ = 0;

  uint32_t ins_ = 1;
};

template <typename T> inline void Game3dObject::ChangeMaterialMode() {
  T;
    material_ = std::make_unique<CLEYERA::Model3d::Material::ColorMaterial>();
  material_->Create();
}

} // namespace Model3d

} // namespace CLEYERA
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

  void Create();

  void Update();

  void DrawRaster3d();

  void ImGuiUpdate();

#pragma region Get
  const Graphics::RasterPipline_Mode3d &GetRasterMode() const {
    return rasterMode_;
  }

  uint32_t GetLayerNumber() { return layerNumber_; }
#pragma endregion

#pragma region Set
  void SetTexHandle(uint32_t handle) { texHandle_ = handle; }
  void SetName(const std::string &name) { name_ = &name; }
  void SetLayerNumber(uint32_t num) { layerNumber_ = num; }
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


  uint32_t modelHandle_ = 0;
  uint32_t texHandle_ = 0;

  uint32_t ins_ = 1;

  uint32_t layerNumber_ = 0;
};



} // namespace Model3d

} // namespace CLEYERA
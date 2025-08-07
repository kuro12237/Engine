#include "RasterPiplineManager.h"

using namespace CLEYERA;

using namespace Graphics;

using namespace Raster;

RasterPiplineManager *CLEYERA::Graphics::Raster::RasterPiplineManager::GetInstance() {
  static RasterPiplineManager instance;
  return &instance;
}

void CLEYERA::Graphics::Raster::RasterPiplineManager::Init() {
  commandManager_ = Base::DX::DXCommandManager::GetInstace();
}

void CLEYERA::Graphics::Raster::RasterPiplineManager::SetRootsignature(
    Graphics::RasterPipline_Mode3d mode) {
  ID3D12RootSignature *root = nullptr;
  auto common = common_.lock();
  if (common) {

    if (mode == RasterPipline_Mode3d::DF_MODEL3d) {
      root = common->Getpipline<system::DFModel3dDraw>(mode).lock()->GetRootSignature();
    }
    if (mode == RasterPipline_Mode3d::LINE3d) {
      root = common->Getpipline<system::Line3dDraw>(mode).lock()->GetRootSignature();
    }
  }
  if (!root) {
    assert(0);
  }
  commandManager_->GraphicsRootSignature(root);
}

void CLEYERA::Graphics::Raster::RasterPiplineManager::SetPipline(
    Graphics::RasterPipline_Mode3d mode) {

  ID3D12PipelineState *state = nullptr;

  auto common = common_.lock();
  if (common) {

    if (mode == RasterPipline_Mode3d::DF_MODEL3d) {
      state = common->Getpipline<system::DFModel3dDraw>(mode).lock()->GetPipline();
    }
    if (mode == RasterPipline_Mode3d::LINE3d) {
      state = common->Getpipline<system::Line3dDraw>(mode).lock()->GetPipline();
    }
  }
  if (!state) {
    assert(0);
  }
  commandManager_->GraphicsPipelineState(state);
}

void CLEYERA::Graphics::Raster::RasterPiplineManager::SetRootsignature(
    Graphics::RasterPipline_Mode2d mode) {
  ID3D12RootSignature *root = nullptr;
  auto common = common_.lock();
  if (common) {

    if (mode == RasterPipline_Mode2d::Normal) {
      root = common->Getpipline<system::DFSprite2dDraw>(mode).lock()->GetRootSignature();
    }
  }
  if (!root) {
    assert(0);
  }
  commandManager_->GraphicsRootSignature(root);
}

void CLEYERA::Graphics::Raster::RasterPiplineManager::SetPipline(
    Graphics::RasterPipline_Mode2d mode) {
  ID3D12PipelineState *state = nullptr;

  auto common = common_.lock();
  if (common) {

    if (mode == RasterPipline_Mode2d::Normal) {
      state = common->Getpipline<system::DFSprite2dDraw>(mode).lock()->GetPipline();
    }
  }
  if (!state) {
    assert(0);
  }
  commandManager_->GraphicsPipelineState(state);
}

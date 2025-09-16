#include "RasterPiplineCommon.h"

void CLEYERA::Graphics::Raster::system::RasterPiplineCommon::Init() {

  using mode = RasterPipline_Mode3d;
  using mode2d = RasterPipline_Mode2d;
  using post = PostEffect_Mode;

  piplines3d_[mode::DF_MODEL3d] = std::make_shared<system::DFModel3dDraw>();
  piplines3d_[mode::DF_MODEL3d]->SetMode(mode::DF_MODEL3d);
  piplines3d_[mode::Normal_MODEL3d] =
      std::make_shared<system::NormalModel3dDraw>();
  piplines3d_[mode::Normal_MODEL3d]->SetMode(mode::Normal_MODEL3d);

  piplines3d_[mode::LINE3d] = std::make_shared<system::Line3dDraw>();
  piplines3d_[mode::LINE3d]->SetMode(mode::LINE3d);

  piplines2d_[mode2d::Normal] = std::make_shared<system::DFSprite2dDraw>();
  piplines2d_[mode2d::Normal]->SetMode(mode2d::Normal);

  piplinesPostEffect_[PostEffect_Mode::Copy] =
      std::make_shared<system::PostEffectCopy>();
  piplinesPostEffect_[PostEffect_Mode::Copy]->SetMode(post::Copy);

  for (auto obj : piplines3d_) {

    auto it = obj.second;
    it->Init();
    it->Create();
  }
  for (auto obj : piplines2d_) {

    auto it = obj.second;
    it->Init();
    it->Create();
  }

  for (auto obj : piplinesPostEffect_) {

    auto it = obj.second;
    it->Init();
    it->Create();
  }
}
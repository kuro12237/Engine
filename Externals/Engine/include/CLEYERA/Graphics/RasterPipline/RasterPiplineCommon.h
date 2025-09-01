#pragma once
#include "RasterEnum.h"
#include "pipline/RasterPiplineCompornent.h"

#include "../../SystemLogManager/ConvertString.h"

#include "pipline/DF/DFModel3dDraw.h"
#include "pipline/Line/Line3dDraw.h"
#include"pipline/2d/DF/DFSprite2dDraw.h"

namespace CLEYERA {

namespace Graphics {

namespace Raster {

namespace system {

/// <summary>
/// パイプラインの作成クラス
/// </summary>
class RasterPiplineCommon {
public:
  RasterPiplineCommon() {};
  ~RasterPiplineCommon() {};

  void Init();

  template <typename T> std::weak_ptr<T> Getpipline(RasterPipline_Mode3d mode) {
    return dynamic_pointer_cast<T>(piplines3d_[mode]);
  }
  template <typename T> std::weak_ptr<T> Getpipline(RasterPipline_Mode2d mode) {
    return dynamic_pointer_cast<T>(piplines2d_[mode]);
  }

private:
  std::map<RasterPipline_Mode3d, std::shared_ptr<RasterPiplineCompornent>> piplines3d_;
  std::map<RasterPipline_Mode2d, std::shared_ptr<RasterPiplineCompornent>> piplines2d_;
};

} // namespace system
} // namespace Raster
} // namespace Graphics
} // namespace CLEYERA
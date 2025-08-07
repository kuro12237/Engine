#pragma once

#include "../../RasterPiplineCompornent.h"

namespace CLEYERA {

namespace Graphics {

namespace Raster {

namespace system {

class DFSprite2dDraw : public RasterPiplineCompornent {
public:
  DFSprite2dDraw() {};
  ~DFSprite2dDraw() {};

  void SettingShader() override;
  void SettingRootParam() override;
  void SettingSampler() override;
  void SettingInput() override;

private:
  D3D12_DESCRIPTOR_RANGE descriptorRangeVertices[1] = {};
};

} // namespace system
} // namespace Raster
} // namespace Graphics
} // namespace CLEYERA
#pragma once
#include "../RasterPiplineCompornent.h"

namespace CLEYERA {

namespace Graphics {

namespace Raster {

namespace system {

class NormalModel3dDraw : public RasterPiplineCompornent {
public:
  NormalModel3dDraw() {};
  ~NormalModel3dDraw() {};

  void SettingShader() override;
  void SettingRootParam() override;
  void SettingSampler() override;
  void SettingInput() override;
  void SettingDepth() override;
  void RtvSetting() override;

private:
  D3D12_DESCRIPTOR_RANGE worldDescriptor[1] = {};

  D3D12_DESCRIPTOR_RANGE materialDescriptor[1] = {};
  D3D12_DESCRIPTOR_RANGE descriptorRangeVertices[1] = {};

  D3D12_DESCRIPTOR_RANGE NormalDescriptor[1] = {};
};

} // namespace system
} // namespace Raster
} // namespace Graphics
} // namespace CLEYERA
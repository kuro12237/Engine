#pragma once
#include "../RasterPiplineCompornent.h"

namespace CLEYERA {

namespace Graphics {

namespace Raster {

namespace system {

class Line3dDraw : public RasterPiplineCompornent {
 public:
   Line3dDraw() {};
   ~Line3dDraw() {};

   void SettingShader() override;
   void SettingRootParam() override;
   void SettingSampler() override;
   void SettingInput() override;

 private:
   D3D12_DESCRIPTOR_RANGE descriptorRangeVertices[1] = {};

   D3D12_DESCRIPTOR_RANGE descriptorRangeColors[1] = {};
};

} // namespace system
} // namespace Raster
} // namespace Graphics
} // namespace CLEYERA
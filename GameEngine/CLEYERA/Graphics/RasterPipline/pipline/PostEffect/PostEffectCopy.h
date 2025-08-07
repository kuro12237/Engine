#pragma once

#include "../RasterPiplineCompornent.h"

namespace CLEYERA {

namespace Graphics {

namespace Raster {

namespace system {

class PostEffectCopy : public RasterPiplineCompornent {
public:
  PostEffectCopy() {};
  ~PostEffectCopy() {};

  void SettingShader() override;
  void SettingRootParam() override;
  void SettingSampler() override;
  void SettingInput() override;
};

} // namespace system
} // namespace Raster
} // namespace Graphics
} // namespace CLEYERA
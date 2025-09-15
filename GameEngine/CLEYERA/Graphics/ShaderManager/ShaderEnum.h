#pragma once
#include "../../pch/Pch.h"

#include "json.hpp"

namespace CLEYERA {

namespace Graphics {

namespace Shader {

/// <summary>
/// シェーダーの種類
/// </summary>
enum class ShaderMode {
  PS,
  VS,
  DS,
  HS,
  GS,
  CS,
  RAYGEN,
  MISS,
  CLOSEST_HIT,
  ANY_HIT,
  INTERSECTION,
  kMax
};
namespace system {
enum class PiplineType {
  Model,
  Sprite,
  PostEffect

};

}
} // namespace Shader
} // namespace Graphics
} // namespace CLEYERA
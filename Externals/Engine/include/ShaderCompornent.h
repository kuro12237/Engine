#pragma once
#include "../../../SystemLogManager/ConvertString.h"
#include "../../RasterPipline/RasterEnum.h"
#include "../ShaderEnum.h"

namespace CLEYERA {

namespace Graphics {

namespace Shader {

namespace system {

class ShaderCommon;

class ShaderCompornent {
public:
  ShaderCompornent() {};
  virtual ~ShaderCompornent() {};

  void Init(ShaderCommon *manager);

  ComPtr<IDxcBlob> CompilerShaderFanc(const std::wstring &filePath, const wchar_t *profile);

  void ShaderFilePath(Shader::ShaderMode mode, std::string name) { shaderFilePath_[name] = mode; }

  IDxcBlob *GetShader(Shader::ShaderMode mode) { return shaders_[mode].Get(); }

  void SetRasterMode(CLEYERA::Graphics::RasterPipline_Mode3d mode) { rasterMode_ = mode; }
  void SetRasterMode(CLEYERA::Graphics::RasterPipline_Mode2d mode) { rasterMode2d_ = mode; }

  void SetIsUse2d(bool f) { isUse2d_ = f; }

private:
  Graphics::RasterPipline_Mode3d rasterMode_;
  Graphics::RasterPipline_Mode2d rasterMode2d_;

  IDxcIncludeHandler *includeHandler_ = nullptr;
  IDxcUtils *utils_ = nullptr;
  IDxcCompiler3 *compiler_ = nullptr;

  bool isUse2d_ = false;

  std::map<std::string, CLEYERA::Graphics::Shader::ShaderMode> shaderFilePath_;
  std::map<CLEYERA::Graphics::Shader::ShaderMode, ComPtr<IDxcBlob>> shaders_;
};
} // namespace system

} // namespace Shader
} // namespace Graphics
} // namespace CLEYERA
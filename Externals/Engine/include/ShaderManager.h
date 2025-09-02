#pragma once
#include "../../pch/Pch.h"
#include "../RasterPipline/RasterEnum.h"
#include "ShaderEnum.h"

#include "ShaderCommon.h"

namespace CLEYERA {

namespace Graphics {

namespace Shader {

class ShaderManager {
 public:
   static ShaderManager *GetInstance();

   void Init();

   static std::vector<char> CompileShader(const std::filesystem::path &hlslFilename);

   void SetCommon(std::weak_ptr<Shader::system::ShaderCommon> c) { common_ = c; }

   IDxcBlob *GetShader(Graphics::RasterPipline_Mode3d pipMode, Shader::ShaderMode shaderMode) { return common_.lock()->GetBlob(pipMode, shaderMode); }
   IDxcBlob *GetShader(Graphics::RasterPipline_Mode2d pipMode, Shader::ShaderMode shaderMode) {
     return common_.lock()->GetBlob(pipMode, shaderMode);
   }

 private:


   std::weak_ptr<Shader::system::ShaderCommon> common_;

   ShaderManager() = default;
   ~ShaderManager() = default;
};
} // namespace Shader
} // namespace Graphics
} // namespace CLEYERA
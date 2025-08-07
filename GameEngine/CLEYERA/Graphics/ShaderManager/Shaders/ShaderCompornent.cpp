#include "ShaderCompornent.h"
#include "../ShaderManager.h"

void CLEYERA::Graphics::Shader::system::ShaderCompornent::Init(ShaderCommon *manager) {

   auto common = manager;

   includeHandler_ = common->GetIncludeHandler();
   utils_ = common->GetUtils();
   compiler_ = common->getCompiler();

   ShaderTag tag;


   if (!isUse2d_) {
     tag = manager->GetFIleName(rasterMode_);
   } else {
     tag = manager->GetFIleName(rasterMode2d_);
   }

   std::string none = "NONE";
   std::string Directory = "Resources/Shaders/";
   if (tag.PS != none) {
      // Pixel Shader の初期化処理
      std::wstring path = ConvertString(Directory+tag.PS);
      shaders_[ShaderMode::PS] = CompilerShaderFanc(path, L"ps_6_0");
   }
   if (tag.VS != none) {
      // Vertex Shader の初期化処理
      std::wstring path = ConvertString(Directory + tag.VS);
      shaders_[ShaderMode::VS] = CompilerShaderFanc(path, L"vs_6_0");
   }
   if (tag.DS != none) {
      // Domain Shader の初期化処理

      std::wstring path = ConvertString(Directory + tag.DS);
      shaders_[ShaderMode::DS] = CompilerShaderFanc(path, L"ds_6_0");
   }
   if (tag.HS != none) {
      // Hull Shader の初期化処理

      std::wstring path = ConvertString(Directory + tag.HS);
      shaders_[ShaderMode::HS] = CompilerShaderFanc(path, L"hs_6_0");
   }
   if (tag.GS != none) {
      // Geometry Shader の初期化処理
      std::wstring path = ConvertString(Directory + tag.GS);
      shaders_[ShaderMode::GS] = CompilerShaderFanc(path, L"gs_6_0");
   }
   if (tag.CS != none) {
      // Compute Shader の初期化処理
      
      std::wstring path = ConvertString(Directory + tag.CS);
      shaders_[ShaderMode::CS] = CompilerShaderFanc(path, L"cs_6_0");
   }
}

ComPtr<IDxcBlob> CLEYERA::Graphics::Shader::system::ShaderCompornent::CompilerShaderFanc(const std::wstring &filePath, const wchar_t *profile) {

   // LogManager::Log(LogManager::ConvertString(std::format(L"Begin CompileShader,path:{},profile:{}\n", filePath, profile)));

   ComPtr<IDxcBlobEncoding> shaderSource = nullptr;
   HRESULT hr = utils_->LoadFile(filePath.c_str(), nullptr, &shaderSource);

   assert(SUCCEEDED(hr));
   DxcBuffer shaderSourceBuffer;
   shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
   shaderSourceBuffer.Size = shaderSource->GetBufferSize();
   shaderSourceBuffer.Encoding = DXC_CP_UTF8;

   LPCWSTR arguments[] = {
       filePath.c_str(), L"-E", L"main", L"-T", profile, L"-Zi", L"-Qembed_debug", L"-Od", L"-Zpr",
   };

   ComPtr<IDxcResult> shaderResult = nullptr;
   hr = compiler_->Compile(&shaderSourceBuffer, arguments, _countof(arguments), includeHandler_, IID_PPV_ARGS(&shaderResult));

   assert(SUCCEEDED(hr));

   ComPtr<IDxcBlobUtf8> shaderError = nullptr;
   shaderResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shaderError), nullptr);
   if (shaderError != nullptr && shaderError->GetStringLength() != 0) {
      //LogManager::Log(shaderError->GetStringPointer());
      OutputDebugStringA(shaderError->GetStringPointer());

      assert(false);
   }

   ComPtr<IDxcBlob> shaderBlob = nullptr;
   hr = shaderResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
   assert(SUCCEEDED(hr));

   // LogManager::Log(LogManager::ConvertString(std::format(L"Compile Succeeded,path:{},profile:{}\n", filePath, profile)));

   return shaderBlob;
}

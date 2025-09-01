#include "ShaderManager.h"
#include <iostream>
using namespace Microsoft::WRL;

CLEYERA::Graphics::Shader::ShaderManager *CLEYERA::Graphics::Shader::ShaderManager::GetInstance() {
   static ShaderManager instance;
   return &instance;
}

void CLEYERA::Graphics::Shader::ShaderManager::Init() {


}

std::vector<char> CLEYERA::Graphics::Shader::ShaderManager::CompileShader(const std::filesystem::path &hlslFilename) {

   HRESULT hr;

   std::ifstream infile(hlslFilename, std::ifstream::binary);
   if (!infile) {
      assert(false && "Failed to open shader file.");
      return {};
   }

   std::wstring fileName = hlslFilename.filename().wstring();
   std::stringstream strstream;
   strstream << infile.rdbuf();
   std::string shaderCode = strstream.str();

   // DXC ライブラリの作成
   ComPtr<IDxcLibrary> lib;
   hr = DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(&lib));
   assert(SUCCEEDED(hr) && "Failed to create DXC Library");

   // DXC コンパイラの作成
   ComPtr<IDxcCompiler> compiler;
   hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&compiler));
   assert(SUCCEEDED(hr) && "Failed to create DXC Compiler");

   // ソースコードのエンコーディング
   ComPtr<IDxcBlobEncoding> source;
   hr = lib->CreateBlobWithEncodingFromPinned(shaderCode.data(), static_cast<UINT32>(shaderCode.size()), CP_UTF8, &source);
   assert(SUCCEEDED(hr) && "Failed to create DXC BlobEncoding");

   // インクルードハンドラ作成
   ComPtr<IDxcIncludeHandler> includeHandler;
   lib->CreateIncludeHandler(&includeHandler);

   // コンパイルオプション
   std::vector<LPCWSTR> arguments = {
       L"-E",           L"main",    // エントリーポイント
       L"-T",           L"lib_6_6", // ターゲットプロファイル
       L"-O3",                      // 最適化レベル
       L"-Zi",
       L"-Qembed_debug" // デバッグ情報
   };

   // シェーダのコンパイル
   ComPtr<IDxcOperationResult> dxcResult;
   hr = compiler->Compile(source.Get(), fileName.c_str(), L"main", L"lib_6_6", arguments.data(), static_cast<UINT32>(arguments.size()), nullptr, 0, includeHandler.Get(), &dxcResult);
   assert(SUCCEEDED(hr) && "Failed to start DXC compilation");

   // コンパイル結果の確認
   dxcResult->GetStatus(&hr);
   if (FAILED(hr)) {
      ComPtr<IDxcBlobEncoding> errorBuffer;
      dxcResult->GetErrorBuffer(&errorBuffer);
      if (errorBuffer) {
         std::cerr << "Shader compilation error: " << (const char *)errorBuffer->GetBufferPointer() << std::endl;
      }
      assert(false && "Shader compilation failed");
      return {};
   }

   // バイナリ取得
   ComPtr<IDxcBlob> blob;
   dxcResult->GetResult(&blob);
   std::vector<char> result(blob->GetBufferSize());
   memcpy(result.data(), blob->GetBufferPointer(), blob->GetBufferSize());

   return result;
}



#include "ShaderCommon.h"
#include "../ShaderManager/ShaderManager.h"

void CLEYERA::Graphics::Shader::system::ShaderCommon::Init() {

  HRESULT hr = {};

  hr = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&utils_));
  assert(SUCCEEDED(hr));

  hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&compiler_));
  assert(SUCCEEDED(hr));

  hr = utils_->CreateDefaultIncludeHandler(&includeHandler_);
  assert(SUCCEEDED(hr));

  // LoadJson();
  fileNames_[RasterPipline_Mode3d::DF_MODEL3d].PiplineName = "DF_MODEL3d";
  fileNames_[RasterPipline_Mode3d::DF_MODEL3d].PS = "Rasterization/DFDraw3d/DFDraw3d_PS.hlsl";
  fileNames_[RasterPipline_Mode3d::DF_MODEL3d].VS = "Rasterization/DFDraw3d/DFDraw3d_VS.hlsl";

  fileNames_[RasterPipline_Mode3d::LINE3d].PiplineName = "LINE3d";
  fileNames_[RasterPipline_Mode3d::LINE3d].PS = "Rasterization/Line3d/LineDraw3d_PS.hlsl";
  fileNames_[RasterPipline_Mode3d::LINE3d].VS = "Rasterization/Line3d/LineDraw3d_VS.hlsl";

  fileNames2d_[RasterPipline_Mode2d::Normal].PiplineName = "Normal";
  fileNames2d_[RasterPipline_Mode2d::Normal].PS = "Rasterization/DFDraw2d/DFDraw2d_PS.hlsl";
  fileNames2d_[RasterPipline_Mode2d::Normal].VS = "Rasterization/DFDraw2d/DFDraw2d_VS.hlsl";

  for (int i = 1; i < static_cast<int>(RasterPipline_Mode3d::kNum); i++) {
    auto mode = static_cast<RasterPipline_Mode3d>(i);
    compornemts_[mode] = std::make_shared<ShaderCompornent>();
    compornemts_[mode]->SetRasterMode(mode);

    compornemts_[mode]->ShaderFilePath(ShaderMode::PS, fileNames_[mode].PS);
    compornemts_[mode]->ShaderFilePath(ShaderMode::VS, fileNames_[mode].VS);
    compornemts_[mode]->ShaderFilePath(ShaderMode::DS, fileNames_[mode].DS);
    compornemts_[mode]->ShaderFilePath(ShaderMode::GS, fileNames_[mode].GS);
    compornemts_[mode]->ShaderFilePath(ShaderMode::HS, fileNames_[mode].HS);
    compornemts_[mode]->ShaderFilePath(ShaderMode::CS, fileNames_[mode].CS);
    compornemts_[mode]->ShaderFilePath(ShaderMode::RAYGEN, fileNames_[mode].RAYGEN);
    compornemts_[mode]->ShaderFilePath(ShaderMode::CLOSEST_HIT, fileNames_[mode].CLOSEST_HIT);
    compornemts_[mode]->ShaderFilePath(ShaderMode::ANY_HIT, fileNames_[mode].ANY_HIT);
    compornemts_[mode]->ShaderFilePath(ShaderMode::MISS, fileNames_[mode].MISS);
    compornemts_[mode]->ShaderFilePath(ShaderMode::INTERSECTION, fileNames_[mode].INTERSECTION);

    compornemts_[mode]->Init(this);
  }

  for (int i = 1; i < static_cast<int>(RasterPipline_Mode2d::kNum); i++) {
    auto mode = static_cast<RasterPipline_Mode2d>(i);
    compornemts2d_[mode] = std::make_shared<ShaderCompornent>();
    compornemts2d_[mode]->SetRasterMode(mode);
    compornemts2d_[mode]->SetIsUse2d(true);

    compornemts2d_[mode]->ShaderFilePath(ShaderMode::PS, fileNames2d_[mode].PS);
    compornemts2d_[mode]->ShaderFilePath(ShaderMode::VS, fileNames2d_[mode].VS);
    compornemts2d_[mode]->ShaderFilePath(ShaderMode::DS, fileNames2d_[mode].DS);
    compornemts2d_[mode]->ShaderFilePath(ShaderMode::GS, fileNames2d_[mode].GS);
    compornemts2d_[mode]->ShaderFilePath(ShaderMode::HS, fileNames2d_[mode].HS);
    compornemts2d_[mode]->ShaderFilePath(ShaderMode::CS, fileNames2d_[mode].CS);
    compornemts2d_[mode]->ShaderFilePath(ShaderMode::RAYGEN, fileNames2d_[mode].RAYGEN);
    compornemts2d_[mode]->ShaderFilePath(ShaderMode::CLOSEST_HIT, fileNames2d_[mode].CLOSEST_HIT);
    compornemts2d_[mode]->ShaderFilePath(ShaderMode::ANY_HIT, fileNames2d_[mode].ANY_HIT);
    compornemts2d_[mode]->ShaderFilePath(ShaderMode::MISS, fileNames2d_[mode].MISS);
    compornemts2d_[mode]->ShaderFilePath(ShaderMode::INTERSECTION, fileNames2d_[mode].INTERSECTION);

    compornemts2d_[mode]->Init(this);
  }
}

void CLEYERA::Graphics::Shader::system::ShaderCommon::LoadJson() {
  // 読み込むJSONファイルのフルパスを合成する

  // 読み込み用ファイルストリーム
  std::ifstream ifs;
  // ファイルを読み込み用に開く
  ifs.open(filePath_);

  // ファイルオープン失敗?
  if (ifs.fail()) {
    std::string message = "Failed open data file for write.";
    MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
    assert(0);
    return;
  }

  nlohmann::json root;

  ifs >> root;
  ifs.close();
  // デバッグ出力を追加して root の内容を確認
  std::cout << "Root JSON content: " << root.dump(4) << std::endl;

  nlohmann::json::iterator itGroup = root.find("Shaders");

  // デバッグ出力を追加して itGroup の内容を確認
  if (itGroup == root.end()) {
    std::cerr << "Shaders key not found in JSON file." << std::endl;
    return;
  }

  std::cout << "Number of shader entries: " << itGroup->size() << std::endl;

  for (nlohmann::json::iterator itItem = itGroup->begin(); itItem != itGroup->end(); ++itItem) {

    if (itItem->is_object()) {
      ShaderTag tag = itItem.value();
      SetShaderName(tag);
    }
  }
}

void CLEYERA::Graphics::Shader::system::ShaderCommon::SetShaderName(const ShaderTag &tag) {

  std::string pip = tag.PiplineName;

  RasterPipline_Mode3d rasterMode = RasterHandler(tag.PiplineName);
  fileNames_[rasterMode] = tag;
}

CLEYERA::Graphics::Shader::ShaderMode
CLEYERA::Graphics::Shader::system::ShaderCommon::TagHandler(std::string tag) {

  using mode = ShaderMode;

  if (tag == "PS")
    return mode::PS;
  if (tag == "VS")
    return mode::VS;
  if (tag == "DS")
    return mode::DS;
  if (tag == "HS")
    return mode::HS;
  if (tag == "GS")
    return mode::GS;
  if (tag == "CS")
    return mode::CS;
  if (tag == "RAYGEN")
    return mode::RAYGEN;
  if (tag == "MISS")
    return mode::MISS;
  if (tag == "CLOSEST_HIT")
    return mode::CLOSEST_HIT;
  if (tag == "ANY_HIT")
    return mode::ANY_HIT;
  if (tag == "INTERSECTION")
    return mode::INTERSECTION;

  return mode::PS;
}

CLEYERA::Graphics::RasterPipline_Mode3d
CLEYERA::Graphics::Shader::system::ShaderCommon::RasterHandler(std::string tag) {

  if (tag == "DF_MODEL3d") {
    return RasterPipline_Mode3d::DF_MODEL3d;
  }
  if (tag == "ANOTHER_MODEL") {
    return RasterPipline_Mode3d::LINE3d;
  }

  return RasterPipline_Mode3d::NONE;
}

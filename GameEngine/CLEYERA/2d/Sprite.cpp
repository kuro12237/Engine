#include "Sprite.h"

CLEYERA::Sprite2d::Sprite::Sprite() {
  cameraManager = Manager::CameraManager::GetInstance();
  layerManager_ = System::LayerManager::GetInstance();
  texManager_ = CLEYERA::Manager::TexManager::GetInstance();
  commandManager_ = Base::DX::DXCommandManager::GetInstace();
  piplineManager_ =
      CLEYERA::Graphics::Raster::RasterPiplineManager::GetInstance();

  this->layerNumber_ = layerManager_->RegisterLayer(layerNumber_);
}

void CLEYERA::Sprite2d::Sprite::Create() {

  mesh_ = std::make_unique<System::SpriteMesh>();
  mesh_->Create();

  meshData_.resize(4);
  mesh_->SetMeshData(meshData_);

  material_ = std::make_unique<CLEYERA::Model3d::Material::ColorMaterial>();
  material_->Create();
  auto data = dynamic_cast<CLEYERA::Model3d::Material::ColorMaterial *>(
      material_.get());
  data->SetParam(&colors_);
}

void CLEYERA::Sprite2d::Sprite::TransfarBuf() { 
    
    mesh_->Transfar(); }

void CLEYERA::Sprite2d::Sprite::Draw() {

  piplineManager_->SetRootsignature(piplineMode::Normal);
  piplineManager_->SetPipline(piplineMode::Normal);

  mesh_->CommandIBVB();

  cameraManager->BindCommand(0);

  this->wtCallFunc_(1);

  auto data = texManager_->GetTexData(*texHandle_);
  auto handle = Base::DX::DXDescripterManager::GetInstance()->GetSRVGPUHandle(
      data.lock()->GetSrvIndex());
  commandManager_->GraphicsDescripterTable(2, handle);

  material_->Bind(3);

  commandManager_->DrawIndexCall(6);
}

void CLEYERA::Sprite2d::Sprite::Update() {
  // 左上
  meshData_[0].vertex.x = -anker_->x * size_->x;
  meshData_[0].vertex.y = (1.0f - anker_->y) * size_->y;
  meshData_[0].vertex.w = 1.0f;

  // 左下
  meshData_[1].vertex.x = -anker_->x * size_->x;
  meshData_[1].vertex.y = -anker_->y * size_->y;
  meshData_[1].vertex.w = 1.0f;

  // 右下
  meshData_[2].vertex.x = (1.0f - anker_->x) * size_->x;
  meshData_[2].vertex.y = -anker_->y * size_->y;
  meshData_[2].vertex.w = 1.0f;

  // 右上
  meshData_[3].vertex.x = (1.0f - anker_->x) * size_->x;
  meshData_[3].vertex.y = (1.0f - anker_->y) * size_->y;
  meshData_[3].vertex.w = 1.0f;

  // テクスチャ座標も同じ順で
  meshData_[0].texCoord = *LeftTop_;     // 左上（画像的には下）
  meshData_[1].texCoord = *LeftBottom;   // 左下（画像的には上）
  meshData_[2].texCoord = *RightBottom_; // 右下（画像的には上）
  meshData_[3].texCoord = *RightTop_;    // 右上（画像的には下）

  material_->Update();
  mesh_->Transfar();
}

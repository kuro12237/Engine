#include "RenderManager.h"

void CLEYERA::Manager::RenderManager::Init() {

  auto obj = Manager::ObjectManager::GetInstance();

  postEffect_ = CLEYERA::Manager::PostEffectManager::GetInstance();

  this->objects_ = &obj->GetObjects();
  this->instancingData_ = &obj->GetInstancingData();
}

void CLEYERA::Manager::RenderManager::Update() {}

void CLEYERA::Manager::RenderManager::Draw3d() {

  auto piplineManager_ = Graphics::Raster::RasterPiplineManager::GetInstance();
  auto cameraManager_ = Manager::CameraManager::GetInstance();
  auto lightManager = Manager::LightManager::GetInstance();
  auto texManager_ = Manager::TexManager::GetInstance();
  auto commandManager_ = Base::DX::DXCommandManager::GetInstace();

  piplineManager_->SetRootsignature(Graphics::RasterPipline_Mode3d::DF_MODEL3d);
  piplineManager_->SetPipline(Graphics::RasterPipline_Mode3d::DF_MODEL3d);

  for (auto &data : *instancingData_) {
    auto &it = data.second;

    cameraManager_->BindCommand(0);

    it.worldIns->Command(1);

    auto data = texManager_->GetTexData(it.model.lock()->GetTexHandle());
    auto handle = Base::DX::DXDescripterManager::GetInstance()->GetSRVGPUHandle(
        data.lock()->GetSrvIndex());
    commandManager_->GraphicsDescripterTable(2, handle);

    lightManager->DirectionLightCommandBind(3);

    cameraManager_->BindCommand(4);

    it.MaterialIns->Command(5);
    // 頂点、インデックス、形状設定
    it.model.lock()->RasterDraw3d();

    commandManager_->DrawIndexCall(
        UINT(it.model.lock()->GetMeshData()->GetData().indecs.size()), it.max);
  }
}

void CLEYERA::Manager::RenderManager::PreDraw() { postEffect_->PreDraw(); 

}

void CLEYERA::Manager::RenderManager::PostDraw() { postEffect_->PostDraw(); }

void CLEYERA::Manager::RenderManager::PostEffectDraw() {

  auto piplineManager_ = Graphics::Raster::RasterPiplineManager::GetInstance();
  auto cameraManager_ = Manager::CameraManager::GetInstance();
  auto commandManager_ = Base::DX::DXCommandManager::GetInstace();
  using buf = CLEYERA::Manager::System::PostEffectBuf;

  piplineManager_->SetRootsignature(Graphics::PostEffect_Mode::Copy);
  piplineManager_->SetPipline(Graphics::PostEffect_Mode::Copy);

  postEffect_->CommandCall(buf::Vert);

  cameraManager_->BindCommand(0);
  postEffect_->CommandCall(buf::World, 1);
  postEffect_->CommandCall(buf::Albedo, 2);
  postEffect_->CommandCall(buf::Normal, 3);
  postEffect_->CommandCall(buf::Depth, 4);

  cameraManager_->BindCommand(5);
  LightManager::GetInstance()->DirectionLightCommandBind(6);

  commandManager_->DrawCall(postEffect_->GetVertData().size(), 1);
}

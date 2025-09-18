#include "RenderManager.h"

void CLEYERA::Manager::RenderManager::Init() {

  auto obj = Manager::ObjectManager::GetInstance();

  postEffect_ = CLEYERA::Manager::PostEffectManager::GetInstance();

  this->objects_ = &obj->GetObjects();
  this->instancingData_ = &obj->GetInstancingData();
}

void CLEYERA::Manager::RenderManager::Update() {}

void CLEYERA::Manager::RenderManager::Draw3d() {
  for (auto &ins : *instancingData_) {

    auto &it = ins.second;
    if (!it.worldIns)
      return;
    it.model.lock()->Update();
    it.worldIns->Update();
    it.MaterialIns->Update();
  }
  auto piplineManager_ = Graphics::Raster::RasterPiplineManager::GetInstance();
  auto cameraManager_ = Manager::CameraManager::GetInstance();
  auto lightManager = Manager::LightManager::GetInstance();
  auto texManager_ = Manager::TexManager::GetInstance();
  auto commandManager_ = Base::DX::DXCommandManager::GetInstace();
  auto descManager_ = Base::DX::DXDescripterManager::GetInstance();
  using DrawMode = Graphics::RasterPipline_Mode3d;

  for (auto &data : *instancingData_) {
    auto &it = data.second;
    auto model = it.model.lock();
    auto albedData =
        texManager_->GetTexData(model->GetAlbedoTexHandle()).lock();
    auto albedHandle = descManager_->GetSRVGPUHandle(albedData->GetSrvIndex());

    piplineManager_->SetRootsignature(it.drawMode_);
    piplineManager_->SetPipline(it.drawMode_);

    switch (it.drawMode_) {
    case DrawMode::DF_MODEL3d:
      cameraManager_->BindCommand(0);
      it.worldIns->Command(1);
      commandManager_->GraphicsDescripterTable(2, albedHandle);
      lightManager->DirectionLightCommandBind(3);
      cameraManager_->BindCommand(4);
      it.MaterialIns->Command(5);
      break;
    case DrawMode::Normal_MODEL3d: {

      auto normalData =
          texManager_->GetTexData(model->GetNormalTexHandle()).lock();
      auto normalHandle =
          descManager_->GetSRVGPUHandle(normalData->GetSrvIndex());

      cameraManager_->BindCommand(0);
      it.worldIns->Command(1);
      commandManager_->GraphicsDescripterTable(2, albedHandle);
      lightManager->DirectionLightCommandBind(3);
      cameraManager_->BindCommand(4);
      it.MaterialIns->Command(5);
      commandManager_->GraphicsDescripterTable(6, normalHandle);
      break;
    }

    default:
      break;
    }

    model->RasterDraw3d();
    commandManager_->DrawIndexCall(
        UINT(model->GetMeshData()->GetData().indecs.size()), it.max);
  }
}

void CLEYERA::Manager::RenderManager::PreDraw() { postEffect_->PreDraw(); }

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

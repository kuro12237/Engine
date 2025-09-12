#include "Game3dObject.h"

void CLEYERA::Model3d::Game3dObject::Create() {
  modelManager_ = Manager::ModelManager::GetInstance();
  cameraManager_ = Manager::CameraManager::GetInstance();
  texManager_ = Manager::TexManager::GetInstance();
  lightManager = Manager::LightManager::GetInstance();

  commandManager_ = Base::DX::DXCommandManager::GetInstace();

  WTCreate(ins_);

}

void CLEYERA::Model3d::Game3dObject::Update() {

  this->WorldMatUpdate();

  this->ConvertMat();
}

void CLEYERA::Model3d::Game3dObject::DrawRaster3d() {

  /// WTをマップ
  this->SetWorldTransfar();

  cameraManager_->BindCommand(0);
  // this->BindWT(1);
  lightManager->DirectionLightCommandBind(3);

  this->BindWT(4);

  cameraManager_->BindCommand(5);
  // 頂点、インデックス、形状設定
  // model_->RasterDraw3d();

  auto data = texManager_->GetTexData(texHandle_);
  auto handle = Base::DX::DXDescripterManager::GetInstance()->GetSRVGPUHandle(
      data.lock()->GetSrvIndex());
  commandManager_->GraphicsDescripterTable(2, handle);

  // commandManager_->DrawIndexCall(UINT(model_->GetMeshData()->GetData().indecs.size()));
}

void CLEYERA::Model3d::Game3dObject::ImGuiUpdate() {

  if (!name_) {
    return;
  }

  if (*name_ == "") {
    return;
  }

  if (ImGui::TreeNode(name_->c_str())) {
    TransformImGuiUpdate();

    ImGui::TreePop();
  }
}

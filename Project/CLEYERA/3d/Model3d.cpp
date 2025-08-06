#include "Model3d.h"

void CLEYERA::Model3d::Model::Init() {

   commandManager_= Base::DX::DXCommandManager::GetInstace();
   commandManager_->CommandClose();
}

void CLEYERA::Model3d::Model::Update() {}

void CLEYERA::Model3d::Model::RasterDraw3d() {

   mesh_->CommandBindVB();
   mesh_->CommandBindIB();

   commandManager_->SetTopology();   

}

void CLEYERA::Model3d::Model::ImGuiUpdate() {

   ImGui::Begin("Vertex_Test");

   ImGui::End();
}

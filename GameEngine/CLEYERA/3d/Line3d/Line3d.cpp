#include "Line3d.h"

void CLEYERA::Model3d::Line3d::Init(const size_t lineMax) {

   cameraManager_ = Manager::CameraManager::GetInstance();
   commandManager_ = Base::DX::DXCommandManager::GetInstace();

   lineMax_ = lineMax;

   WTCreate(1);

   mesh_ = std::make_unique<CLEYERA::Model3d::MeshData>();

   system::VertexData vertData;
   vertData.vertices.resize(vertCount_);
   mesh_->SetVertexData(vertData);
   mesh_->CreateVert(vertCount_);

   size_t posMax = lineMax_ * vertCount_;
   
   lineBuf_ = std::make_unique<Base::DX::DXBufferResource<Math::Vector::Vec3>>();
   lineBuf_->SetDevice(Base::DX::DXManager::GetInstance()->GetDevice());
   lineBuf_->Init(posMax);
   lineBuf_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
   lineBuf_->RegisterSRV();

   lineColorBuf_ = std::make_unique<Base::DX::DXBufferResource<Math::Vector::Vec4>>();
   lineColorBuf_->SetDevice(Base::DX::DXManager::GetInstance()->GetDevice());
   lineColorBuf_->Init(posMax);
   lineColorBuf_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
   lineColorBuf_->RegisterSRV();
}

void CLEYERA::Model3d::Line3d::Update() {

   lineBuf_->Map();
   lineBuf_->SetParam(*postions_);
   lineBuf_->UnMap();
   
   lineColorBuf_->Map();
   lineColorBuf_->SetParam(*colors_);
   lineColorBuf_->UnMap();

   this->WorldMatUpdate();
   this->ConvertMat();
   this->SetWorldTransfar();
}

void CLEYERA::Model3d::Line3d::DrawLine3d() {

   cameraManager_->BindCommand(0);
   this->BindWT(1);
   lineBuf_->GraphicsRootDescripterTable(2);
   lineColorBuf_->GraphicsRootDescripterTable(3);
   mesh_->CommandBindVB();
   commandManager_->SetTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
   commandManager_->DrawCall(UINT(vertCount_), UINT(lineMax_));
}

#include "SpriteMesh.h"

CLEYERA::Sprite2d::System::SpriteMesh::SpriteMesh() {

  vertexBuf_ = std::make_unique<Base::DX::DXBufferResource<Mesh2d>>();
  indexBuf_ = std::make_unique<Base::DX::DXBufferResource<int32_t>>();
}

void CLEYERA::Sprite2d::System::SpriteMesh::Create() {

  vertexBuf_->Init(4);
  auto device = Base::DX::DXManager::GetInstance()->GetDevice();
  vertexBuf_->SetDevice(device);
  vertexBuf_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
  vertexBuf_->CreateVertexBufferView();

  index_.resize(6);
  indexBuf_->Init(6);
  indexBuf_->SetDevice(device);
  indexBuf_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
  indexBuf_->CreateIndexBufferView();
}

void CLEYERA::Sprite2d::System::SpriteMesh::Transfar() {
  vertexBuf_->Map();
  vertexBuf_->SetParam(*mesh_);
  vertexBuf_->UnMap();
  vertexBuf_->Update();

  // indexDatesh
  index_.resize(6);
  index_[0] = 0;
  index_[1] = 1;
  index_[2] = 2;
  index_[3] = 0;
  index_[4] = 2;
  index_[5] = 3;

  indexBuf_->Map();
  indexBuf_->SetParam(index_);
  indexBuf_->UnMap();
  indexBuf_->Update();
}

void CLEYERA::Sprite2d::System::SpriteMesh::CommandIBVB() {
  auto commandManager = Base::DX::DXCommandManager::GetInstace();
  commandManager->SetTopology();
  vertexBuf_->VBCommand();

  indexBuf_->IBCommand();
}

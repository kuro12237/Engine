#include "MeshData.h"

void CLEYERA::Model3d::MeshData::Create(aiMesh *mesh) {

  device_ = Base::DX::DXManager::GetInstance()->GetDevice();

  // 合計のサイズ
  byteSize_ =
      static_cast<uint32_t>(sizeof(system::VertexForGPU) * mesh->mNumVertices);

	data_.vertices.resize(mesh->mNumVertices);
  for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
    aiFace &face = mesh->mFaces[faceIndex];
    assert(face.mNumIndices == 3); // 三角形のみ
    for (uint32_t element = 0; element < face.mNumIndices; ++element) {
      uint32_t vertexIndex = face.mIndices[element];
      aiVector3D &position = mesh->mVertices[vertexIndex];
      aiVector3D &normal = mesh->mNormals[vertexIndex];
      aiVector3D &texcoord = mesh->mTextureCoords[0][vertexIndex];
      data_.vertices[vertexIndex].pos = {-position.x, position.y,
                                             position.z, 1.0f};
      data_.vertices[vertexIndex].normal = {-normal.x, normal.y, normal.z};
      data_.vertices[vertexIndex].texCooard = {texcoord.x, texcoord.y};
      // Indexの解析
      data_.indecs.push_back(vertexIndex);
    }
  }

  vertBuf_ =
      std::make_unique<Base::DX::DXBufferResource<system::VertexForGPU>>();
  vertBuf_->SetDevice(device_);

  // バッファの作成
  vertBuf_->Init(data_.vertices.size());
  vertBuf_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD,
                         D3D12_RESOURCE_STATE_GENERIC_READ);
  vertBuf_->CreateVertexBufferView();

  vertBuf_->RegisterSRV();

  vertBuf_->Map();
  vertBuf_->SetParam(data_.vertices);
  vertBuf_->UnMap();

  indexBuf_ = std::make_unique<Base::DX::DXBufferResource<uint32_t>>();
  indexBuf_->SetDevice(device_);

  indexBuf_->Init(data_.indecs.size());
  indexBuf_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD,
                          D3D12_RESOURCE_STATE_GENERIC_READ);
  indexBuf_->CreateIndexBufferView();

  indexBuf_->Map();
  indexBuf_->SetParam(data_.indecs);
  indexBuf_->UnMap();

  indexBuf_->RegisterSRV();

  // Blas
  blas_ = std::make_unique<system::Blas>();
  blas_->SetParamCount(this->data_.vertices.size());
  blas_->SetSize(sizeof(system::VertexForGPU));
  blas_->SetVertexBuf(vertBuf_->GetResource());
  blas_->Init();

  this->shaderName = CLEYERA::Graphics::HitGroup::ALL;
}

void CLEYERA::Model3d::MeshData::CreateVert(size_t size) {
  device_ = Base::DX::DXManager::GetInstance()->GetDevice();

  data_.vertices.resize(size);

  vertBuf_ =
      std::make_unique<Base::DX::DXBufferResource<system::VertexForGPU>>();
  vertBuf_->SetDevice(device_);

  // バッファの作成
  vertBuf_->Init(data_.vertices.size());
  vertBuf_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD,
                         D3D12_RESOURCE_STATE_GENERIC_READ);
  vertBuf_->CreateVertexBufferView();

  vertBuf_->RegisterSRV();

  vertBuf_->Map();
  vertBuf_->SetParam(data_.vertices);
  vertBuf_->UnMap();
}

void CLEYERA::Model3d::MeshData::CommandBindVB() { vertBuf_->VBCommand(); }

void CLEYERA::Model3d::MeshData::CommandBindIB() { indexBuf_->IBCommand(); }

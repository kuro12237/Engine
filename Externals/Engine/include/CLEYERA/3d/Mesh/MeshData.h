#pragma once
#include "../../DX/DXBufferResource/DXBufferResource.h"
#include "../../DX/DXManager.h"
#include "../../pch/Pch.h"
#include "../Blas/Blas.h"
#include"../../Graphics/RaytracingManager/HitGroup.h"

namespace CLEYERA {

namespace Model3d {

namespace system {

/// <summary>
/// 頂点データ
/// </summary>
struct VertexForGPU {

   Math::Vector::Vec4 pos = {};
   Math::Vector::Vec3 normal = {};
   Math::Vector::Vec2 texCooard = {};
   int32_t instanceId = 0;
};

/// <summary>
/// modelのメッシュデータ
/// </summary>
struct VertexData {

   std::vector<VertexForGPU> vertices;
   std::vector<uint32_t> indecs;
};

} // namespace system

/// <summary>
/// メッシュのデータ
/// </summary>
class MeshData {
 public:
   MeshData() {};
   ~MeshData() {};

   /// <summary>
   /// データ作成
   /// </summary>
   void Create(aiMesh *mesh);

   /// <summary>
   /// 商店データのみ生成
   /// </summary>
   void CreateVert(size_t size);

   void CommandBindVB();
   void CommandBindIB();

   void SetVertexData(system::VertexData vertices) {data_ = vertices; }


#pragma region Get
   system::VertexData GetData() const { return data_; }
   uint32_t GetByteSize() { return byteSize_; }

   ID3D12Resource *GetVertBuf() { return vertBuf_->GetResource(); }
   ID3D12Resource *GetBlasBuf() { return blas_->GetResource(); }

   size_t GetVertexBufIndex() { return vertBuf_->GetSRVIndex(); }
   size_t GetIndexBufIndex() { return indexBuf_->GetSRVIndex(); }

   std::wstring GetShaderName() { return shaderName; }
#pragma endregion

 private:
   system::VertexData data_ = {};

   ID3D12Device5 *device_ = nullptr;

   std::unique_ptr<Base::DX::DXBufferResource<system::VertexForGPU>> vertBuf_ = nullptr;
   std::unique_ptr<Base::DX::DXBufferResource<uint32_t>> indexBuf_ = nullptr;
   std::unique_ptr<system::Blas> blas_ = nullptr;

  
   uint32_t byteSize_ = 0;
   std::wstring shaderName = CLEYERA::Graphics::HitGroup::ALL;
};

} // namespace Model3d

} // namespace CLEYERA
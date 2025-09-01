#include "Blas.h"

void CLEYERA::Model3d::system::Blas::Init() {

   device_ = CLEYERA::Base::DX::DXManager::GetInstance()->GetDevice();
   // BLAS を作成.
   D3D12_RAYTRACING_GEOMETRY_DESC geomDesc{};
   geomDesc.Type = D3D12_RAYTRACING_GEOMETRY_TYPE_TRIANGLES;
   geomDesc.Flags = D3D12_RAYTRACING_GEOMETRY_FLAG_OPAQUE;
   geomDesc.Triangles.VertexBuffer.StartAddress = vertexbuf_->GetGPUVirtualAddress();
   geomDesc.Triangles.VertexBuffer.StrideInBytes = size_;
   geomDesc.Triangles.VertexFormat = DXGI_FORMAT_R32G32B32_FLOAT;
   geomDesc.Triangles.VertexCount = static_cast<UINT>(paramCount_);

   D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC buildASDesc{};
   auto &inputs = buildASDesc.Inputs; 
   inputs.Type = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL;
   inputs.DescsLayout = D3D12_ELEMENTS_LAYOUT_ARRAY;
   inputs.Flags = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_NONE;
   inputs.NumDescs = 1;
   inputs.pGeometryDescs = &geomDesc;

   // 必要なメモリ量を求める.
   D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO blasPrebuild{};
   device_->GetRaytracingAccelerationStructurePrebuildInfo(&inputs, &blasPrebuild);

   // スクラッチバッファを確保.
   std::unique_ptr<Base::DX::DXBufferResource<int32_t>> blasScratch = std::make_unique<Base::DX::DXBufferResource<int32_t>>();
   blasScratch->SetDevice(device_);
   blasScratch->Init();

   blasScratch->DFCreateBuffer(blasPrebuild.ResultDataMaxSizeInBytes, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_COMMON, D3D12_HEAP_TYPE_DEFAULT);

   // CommonからUAVに変更
   D3D12_RESOURCE_BARRIER barrier = {};
   barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
   barrier.Transition.pResource = blasScratch->GetResource();
   barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
   barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
   barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
   ID3D12GraphicsCommandList4 *list = Base::DX::DXCommandManager::GetInstace()->GetCommandList();
   list->ResourceBarrier(1, &barrier);

   // BLAS 用メモリ(バッファ)を確保.
   buf_ = std::make_unique<Base::DX::DXBufferResource<int32_t>>();
   buf_->SetDevice(device_);
   buf_->Init();
   buf_->DFCreateBuffer(blasPrebuild.ResultDataMaxSizeInBytes, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE, D3D12_HEAP_TYPE_DEFAULT);

   // Acceleration Structure
   buildASDesc.ScratchAccelerationStructureData = blasScratch->GetResource()->GetGPUVirtualAddress();
   buildASDesc.DestAccelerationStructureData = buf_->GetResource()->GetGPUVirtualAddress();


   list->BuildRaytracingAccelerationStructure(&buildASDesc, 0, nullptr);

   std::unique_ptr<Base::DX::DXBarrier> barrier_ = std::make_unique<Base::DX::DXBarrier>();

   barrier_->Init();
   barrier_->SetBuffer(buf_->GetResource());
   barrier_->SetBarrierType(0, D3D12_RESOURCE_BARRIER_TYPE_UAV);
   barrier_->Barrier();

   auto commandManager = Base::DX::DXCommandManager::GetInstace();
   commandManager->CommandClose();

}
void CLEYERA::Model3d::system::Blas::Update() {



};
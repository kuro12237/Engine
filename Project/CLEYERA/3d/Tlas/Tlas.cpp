#include "Tlas.h"

void CLEYERA::Model3d::system::Tlas::Init() {

   auto dxManager = Base::DX::DXManager::GetInstance();
   ID3D12Device5 *device = Base::DX::DXManager::GetInstance()->GetDevice();

   size_t size = instanceDesc_.size() * sizeof(D3D12_RAYTRACING_INSTANCE_DESC);

   instanceDescBuf = std::make_unique<Base::DX::DXBufferResource<int32_t>>();

   instanceDescBuf->SetDevice(dxManager->GetDevice());
   instanceDescBuf->DFCreateBuffer(size, D3D12_RESOURCE_FLAG_NONE, D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_HEAP_TYPE_UPLOAD);
   instanceDescBuf->WriteMemory(instanceDesc_.data(), sizeof(D3D12_RAYTRACING_INSTANCE_DESC));

   D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC buildASDesc{};
   auto &inputs = buildASDesc.Inputs;
   inputs.Type = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL;
   inputs.DescsLayout = D3D12_ELEMENTS_LAYOUT_ARRAY;
   inputs.Flags = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_NONE;
   inputs.NumDescs = 1;

   // 必要なメモリ量を求める.
   D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO tlasPrebuild{};
   device->GetRaytracingAccelerationStructurePrebuildInfo(&inputs, &tlasPrebuild);

   // スクラッチバッファを確保.
   std::unique_ptr<Base::DX::DXBufferResource<int32_t>> tlasScratch = std::make_unique<Base::DX::DXBufferResource<int32_t>>();
   tlasScratch->SetDevice(device);
   tlasScratch->Init();

   tlasScratch->DFCreateBuffer(tlasPrebuild.ResultDataMaxSizeInBytes, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_COMMON, D3D12_HEAP_TYPE_DEFAULT);

   // コマンドリストでリソースの状態を変更
   D3D12_RESOURCE_BARRIER barrier = {};
   barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
   barrier.Transition.pResource = tlasScratch->GetResource();
   barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
   barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
   barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
   ID3D12GraphicsCommandList4 *list = Base::DX::DXCommandManager::GetInstace()->GetCommandList();
   list->ResourceBarrier(1, &barrier);

   buf_ = std::make_unique<Base::DX::DXBufferResource<int32_t>>();
   buf_->SetDevice(device);
   buf_->Init();
   buf_->DFCreateBuffer(tlasPrebuild.ResultDataMaxSizeInBytes, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE, D3D12_HEAP_TYPE_DEFAULT);

   // Acceleration Structure 構築.
   buildASDesc.Inputs.InstanceDescs = instanceDescBuf->GetResource()->GetGPUVirtualAddress();
   buildASDesc.ScratchAccelerationStructureData = tlasScratch->GetResource()->GetGPUVirtualAddress();
   buildASDesc.DestAccelerationStructureData = buf_->GetResource()->GetGPUVirtualAddress();

   // コマンドリストに積んで実行する.

   list->BuildRaytracingAccelerationStructure(&buildASDesc, 0, nullptr);

   std::unique_ptr<Base::DX::DXBarrier> barrier_ = std::make_unique<Base::DX::DXBarrier>();

   barrier_->Init();
   barrier_->SetBuffer(buf_->GetResource());
   barrier_->SetBarrierType(0, D3D12_RESOURCE_BARRIER_TYPE_UAV);
   barrier_->Barrier();

   D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
   srvDesc.ViewDimension = D3D12_SRV_DIMENSION_RAYTRACING_ACCELERATION_STRUCTURE;
   srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
   srvDesc.RaytracingAccelerationStructure.Location = buf_->GetResource()->GetGPUVirtualAddress();
   buf_->RegisterSRV(srvDesc);

   auto commandManager = Base::DX::DXCommandManager::GetInstace();
   commandManager->CommandClose();
}

void CLEYERA::Model3d::system::Tlas::Update(std::vector<std::weak_ptr<Model3d::Game3dObject>> &obj) {
    
     size_t size = obj.size();

   for (size_t i = 0; i < size; i++) {

      auto it = obj[i].lock();

      memcpy(&instanceDesc_[i].Transform, &it->GetMat3x4(), sizeof(Math::Matrix::Mat3x4));
   }
    instanceDescBuf->WriteMemory(instanceDesc_.data(), sizeof(D3D12_RAYTRACING_INSTANCE_DESC));


}

void CLEYERA::Model3d::system::Tlas::BufferBind() { buf_->ComputeRootDescripterTable(0); }

void CLEYERA::Model3d::system::Tlas::SetCreateObject(std::vector<std::weak_ptr<Model3d::Game3dObject>> &obj) {

   size_t size = obj.size();

   instanceDesc_.resize(size);

   D3D12_RAYTRACING_INSTANCE_DESC instanceDesc{};
   instanceDesc.InstanceMask = 0xFF;
   instanceDesc.Flags = D3D12_RAYTRACING_INSTANCE_FLAG_NONE;

   for (size_t i = 0; i < size; i++) {

      auto it = obj[i].lock();

      instanceDesc_[i] = instanceDesc;

      memcpy(&instanceDesc_[i].Transform, &it->GetMat3x4(), sizeof(Math::Matrix::Mat3x4));
      instanceDesc_[i].InstanceID = 0;
      instanceDesc_[i].InstanceMask = 0xFF;
      instanceDesc_[i].InstanceContributionToHitGroupIndex = 0;
      instanceDesc_[i].Flags = D3D12_RAYTRACING_INSTANCE_FLAG_NONE;
      instanceDesc_[i].AccelerationStructure = it->GetModel().lock()->GetMeshData()->GetBlasBuf()->GetGPUVirtualAddress();

   }
}

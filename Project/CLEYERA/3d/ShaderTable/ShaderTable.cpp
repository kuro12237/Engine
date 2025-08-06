#include "ShaderTable.h"

void ShaderTable::Init() {

   device_ = CLEYERA::Base::DX::DXManager::GetInstance()->GetDevice();

   shaderTable_ = std::make_unique<CLEYERA::Base::DX::DXBufferResource<int32_t>>();
   shaderTable_->SetDevice(device_);
   shaderTable_->Init();

   ////アライメント
   // const auto ShaderRecordAlignment = D3D12_RAYTRACING_SHADER_RECORD_BYTE_ALIGNMENT;

   ////OutPut
   // UINT raygenRecordSize = 0;
   // raygenRecordSize += D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES;
   // raygenRecordSize += sizeof(D3D12_GPU_DESCRIPTOR_HANDLE);
   // raygenRecordSize = RoundUp(raygenRecordSize, ShaderRecordAlignment);

   ////IB+VB
   // UINT hitgroupRecordSize = 0;
   // hitgroupRecordSize += D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES;
   // hitgroupRecordSize += sizeof(D3D12_GPU_DESCRIPTOR_HANDLE);
   // hitgroupRecordSize += sizeof(D3D12_GPU_DESCRIPTOR_HANDLE);
   // hitgroupRecordSize = RoundUp(hitgroupRecordSize, ShaderRecordAlignment);

   ////何もしない
   // UINT missRecordSize = 0;
   // missRecordSize += D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES;
   // missRecordSize = RoundUp(missRecordSize, ShaderRecordAlignment);

   // UINT hitgroupCount = 1;
   // UINT raygenSize = 1 * raygenRecordSize;
   // UINT missSize = 1 * missRecordSize;
   // UINT hitGroupSize = hitgroupCount * hitgroupRecordSize;

   // auto tableAlign = D3D12_RAYTRACING_SHADER_TABLE_BYTE_ALIGNMENT;
   // auto raygenRegion = RoundUp(raygenSize, tableAlign);
   // auto missRegion = RoundUp(missSize, tableAlign);
   // auto hitgroupRegion = RoundUp(hitGroupSize, tableAlign);

   //// シェーダーテーブル確保
   // auto tableSize = raygenRegion + missRegion + hitgroupRegion;
   // shaderTable_->DFCreateBuffer(tableSize, D3D12_RESOURCE_FLAG_NONE, D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_HEAP_TYPE_UPLOAD);

   // ComPtr<ID3D12StateObjectProperties> rtsoProps;
   // this->stateObject_.As(&rtsoProps);

   // void *mapped = nullptr;
   // shaderTable_->GetResource()->Map(0, nullptr, &mapped);
   // uint8_t *pStart = static_cast<uint8_t *>(mapped);

   //// RayGeneration
   // auto rgsStart = pStart;
   //{
   //    uint8_t *p = rgsStart;
   //    auto id = rtsoProps->GetShaderIdentifier(L"mainRayGen");

   //   p += WriteShaderIdentifier(p, id);

   //   D3D12_GPU_DESCRIPTOR_HANDLE handle = CLEYERA::Base::DX::DXDescripterManager::GetInstance()->GetSRVGPUHandle(outPutDescripterHandle_);
   //   p += WriteGPUDescriptor(p, handle);
   //}

   ////miss書きこみ
   // auto missStart = pStart + raygenRegion;
   //{
   //    uint8_t *p = missStart;
   //    auto id = rtsoProps->GetShaderIdentifier(L"mainMS");
   //
   //    p += WriteShaderIdentifier(p, id);
   // }

   ////HitGroup
   // auto hitgroupStart = pStart + raygenRegion + missRegion;
   //{
   //    uint8_t *pRecord = hitgroupStart;
   //    // objのデータ書き込み
   //    for (auto obj : objs_) {
   //       auto it = obj.lock();
   //       pRecord = WriteShaderRecord(pRecord, it, hitgroupRecordSize);
   //    }
   // }

   ////情報をセット
   // auto startAddress = shaderTable_->GetResource()->GetGPUVirtualAddress();

   // auto &shaderRecordRG = dispatchRayDesc.RayGenerationShaderRecord;
   // shaderRecordRG.StartAddress = startAddress;
   // shaderRecordRG.SizeInBytes = raygenSize;
   // startAddress += raygenRegion;

   // auto &shaderRecordMS = dispatchRayDesc.MissShaderTable;
   // shaderRecordMS.StartAddress = startAddress;
   // shaderRecordMS.SizeInBytes = missSize;
   // shaderRecordMS.StrideInBytes = missRecordSize;
   // startAddress += missRegion;

   // auto &shaderRecordHG = dispatchRayDesc.HitGroupTable;
   // shaderRecordHG.StartAddress = startAddress;
   // shaderRecordHG.SizeInBytes = hitGroupSize;
   // shaderRecordHG.StrideInBytes = hitgroupRecordSize;
   // startAddress += hitgroupRegion;
   //  各シェーダーレコードは Shader Identifier を保持する.
   UINT recordSize = D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES;

   // グローバルのルートシグネチャ以外の情報を持たないのでレコードサイズはこれだけ.

   // あとはアライメント制約を保つようにする.
   recordSize = RoundUp(recordSize, D3D12_RAYTRACING_SHADER_RECORD_BYTE_ALIGNMENT);

   // シェーダーテーブルのサイズを求める.
   UINT raygenSize = 1 * recordSize;   // 今1つの Ray Generation シェーダー.
   UINT missSize = 1 * recordSize;     // 今1つの Miss シェーダー.
   UINT hitGroupSize = 1 * recordSize; // 今1つの HitGroup を使用.

   // 各テーブルの開始位置にアライメント制約があるので調整する.
   auto tableAlign = D3D12_RAYTRACING_SHADER_TABLE_BYTE_ALIGNMENT;
   UINT raygenRegion = RoundUp(raygenSize, tableAlign);
   UINT missRegion = RoundUp(missSize, tableAlign);
   UINT hitgroupRegion = RoundUp(hitGroupSize, tableAlign);

   // シェーダーテーブル確保.
   auto tableSize = raygenRegion + missRegion + hitgroupRegion;
   shaderTable_->DFCreateBuffer(tableSize, D3D12_RESOURCE_FLAG_NONE, D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_HEAP_TYPE_UPLOAD);

   ComPtr<ID3D12StateObjectProperties> rtsoProps;
   stateObject_.As(&rtsoProps);

   // 各シェーダーレコードを書き込んでいく.
   void *mapped = nullptr;
   shaderTable_->GetResource()->Map(0, nullptr, &mapped);
   uint8_t *pStart = static_cast<uint8_t *>(mapped);

   // RayGeneration 用のシェーダーレコードを書き込み.
   auto rgsStart = pStart;
   {
      uint8_t *p = rgsStart;
      auto id = rtsoProps->GetShaderIdentifier(L"mainRayGen");
      if (id == nullptr) {
         throw std::logic_error("Not found ShaderIdentifier");
      }
      memcpy(p, id, D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES);
      p += D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES;

      // ローカルルートシグネチャ使用時には他のデータを書き込む.
   }

   // Miss Shader 用のシェーダーレコードを書き込み.
   auto missStart = pStart + raygenRegion;
   {
      uint8_t *p = missStart;
      auto id = rtsoProps->GetShaderIdentifier(L"mainMS");
      if (id == nullptr) {
         throw std::logic_error("Not found ShaderIdentifier");
      }
      memcpy(p, id, D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES);
      p += D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES;

      // ローカルルートシグネチャ使用時には他のデータを書き込む.
   }

   // Hit Group 用のシェーダーレコードを書き込み.
   auto hitgroupStart = pStart + raygenRegion + missRegion;
   {
      uint8_t *p = hitgroupStart;
      auto id = rtsoProps->GetShaderIdentifier(CLEYERA::Graphics::HitGroup::ALL);
      if (id == nullptr) {
         throw std::logic_error("Not found ShaderIdentifier");
      }
      memcpy(p, id, D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES);
      p += D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES;

   /*  //  ローカルルートシグネチャ使用時には他のデータを書き込む.
      auto hitgroupStart = pStart + raygenRegion + missRegion;
      {
         uint8_t *pRecord = hitgroupStart;
          //objのデータ書き込み
         for (auto obj : objs_) {
            auto it = obj.lock();
            pRecord = WriteShaderRecord(pRecord, it, hitgroupRecordSize);
         }
      }*/
   }

   // DispatchRays のために情報をセットしておく.
   auto startAddress = shaderTable_->GetResource()->GetGPUVirtualAddress();
   auto &shaderRecordRG = dispatchRayDesc.RayGenerationShaderRecord;
   shaderRecordRG.StartAddress = startAddress;
   shaderRecordRG.SizeInBytes = raygenSize;
   startAddress += raygenRegion;

   auto &shaderRecordMS = dispatchRayDesc.MissShaderTable;
   shaderRecordMS.StartAddress = startAddress;
   shaderRecordMS.SizeInBytes = missSize;
   shaderRecordMS.StrideInBytes = recordSize;
   startAddress += missRegion;

   auto &shaderRecordHG = dispatchRayDesc.HitGroupTable;
   shaderRecordHG.StartAddress = startAddress;
   shaderRecordHG.SizeInBytes = hitGroupSize;
   shaderRecordHG.StrideInBytes = recordSize;
   startAddress += hitgroupRegion;

   dispatchRayDesc.Width = CLEYERA::Base::Win::WinApp::GetKWindowWidth();
   dispatchRayDesc.Height = CLEYERA::Base::Win::WinApp::GetKWindowHeight();
   dispatchRayDesc.Depth = 1;
}

uint8_t *ShaderTable::WriteShaderRecord(uint8_t *dst, std::weak_ptr<CLEYERA::Model3d::Game3dObject> obj, UINT recordSize) {
   ComPtr<ID3D12StateObjectProperties> rtsoProps;
   stateObject_.As(&rtsoProps);
   auto entryBegin = dst;
   auto shader = obj.lock()->GetModel().lock()->GetMeshData()->GetShaderName();
   auto id = rtsoProps->GetShaderIdentifier(shader.c_str());

   dst += WriteShaderIdentifier(dst, id);
   auto descManager = CLEYERA::Base::DX::DXDescripterManager::GetInstance();
   auto mesh = obj.lock()->GetModel().lock()->GetMeshData();
   D3D12_GPU_DESCRIPTOR_HANDLE vb = descManager->GetSRVGPUHandle(mesh->GetVertexBufIndex());
   D3D12_GPU_DESCRIPTOR_HANDLE ib = descManager->GetSRVGPUHandle(mesh->GetIndexBufIndex());

   dst += WriteGPUDescriptor(dst, ib);
   dst += WriteGPUDescriptor(dst, vb);

   dst = entryBegin + recordSize;
   return dst;
}

UINT ShaderTable::WriteShaderIdentifier(void *dst, const void *shaderId) {

   memcpy(dst, shaderId, D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES);
   return D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES;
}

UINT ShaderTable::WriteGPUDescriptor(void *dst, D3D12_GPU_DESCRIPTOR_HANDLE handle) {

   memcpy(dst, &handle, sizeof(handle));
   return UINT(sizeof(handle));
}

#pragma once
#include "../../DX/DXManager.h"
#include "../../WIn/WinApp.h"
#include "../../pch/Pch.h"
#include"../Game3dObject.h"

#include"../../Graphics/RaytracingManager/HitGroup.h"

class ShaderTable {
 public:
   ShaderTable() {};
   ~ShaderTable() {};

   void Init();

   void SetStateObj(ComPtr<ID3D12StateObject> obj) { stateObject_ = obj; }

   D3D12_DISPATCH_RAYS_DESC GetDispatchRayDesc() { return dispatchRayDesc; }

   void SetOutPutDescripterHandle(uint32_t index) { outPutDescripterHandle_ = index; }

   void SetGameObjes(std::vector<std::weak_ptr<CLEYERA::Model3d::Game3dObject>> objs) { objs_ = objs; }

 private:
   uint8_t *WriteShaderRecord(uint8_t *dst, std::weak_ptr<CLEYERA::Model3d::Game3dObject> obj, UINT recordSize);

   UINT WriteShaderIdentifier(void *dst, const void *shaderId);
   UINT WriteGPUDescriptor(void *dst, D3D12_GPU_DESCRIPTOR_HANDLE handle);

   UINT RoundUp(size_t size, UINT align) { return UINT(size + align - 1) & ~(align - 1); }

   std::vector<std::weak_ptr<CLEYERA::Model3d::Game3dObject>> objs_;

   D3D12_DISPATCH_RAYS_DESC dispatchRayDesc;
   ID3D12Device5 *device_ = nullptr;
   ComPtr<ID3D12StateObject> stateObject_ = nullptr;

   uint32_t outPutDescripterHandle_ = 0;

   std::unique_ptr<CLEYERA::Base::DX::DXBufferResource<int32_t>> shaderTable_ = nullptr;
};

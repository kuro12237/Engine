#pragma once

#include "../../DX/DXBarrier/DXBarrier.h"
#include "../../DX/DXManager.h"

namespace CLEYERA {

namespace Graphics {


/// <summary>
/// レイトレーシング管理クラス
/// </summary>
class RaytracingManager {
 public:
   RaytracingManager() = default;
   ~RaytracingManager() = default;

   /// <summary>
   /// 作成
   /// </summary>
   void Create();

   /// <summary>
   /// 前処理
   /// </summary>
   void PreRaytracing();

   /// <summary>
   /// 後処理
   /// </summary>
   void PostRaytracing();

   /// <summary>
   /// 計算
   /// </summary>
   void DispachRay();

#pragma region Get
   ID3D12Resource *GetOutputResource() { return outputBuf_->GetResource(); }
   size_t Gethandle() { return outputBuf_->GetSRVIndex(); }
#pragma endregion

#pragma region Set
   void SetBarrierRTVResource(ID3D12Resource *buf) { barrier_.Transition.pResource = buf; };
   void SetDispathRayDesc(const D3D12_DISPATCH_RAYS_DESC &desc) { dispachRayDesc_ = &desc; }
#pragma endregion

 private:
   /// <summary>
   /// UAV作成
   /// </summary>
   void CreateOutPutUAV();

   CLEYERA::Base::DX::DXManager *dxManager_ = nullptr;
   CLEYERA::Base::DX::DXCommandManager *commandManager_ = nullptr;
   CLEYERA::Base::DX::DXDescripterManager *descripterManager_ = nullptr;

   std::unique_ptr<Base::DX::DXBufferResource<int32_t>> outputBuf_ = nullptr;

   D3D12_RESOURCE_BARRIER barrier_ = {};

   const D3D12_DISPATCH_RAYS_DESC *dispachRayDesc_ = nullptr;
};

} // namespace Graphics

} // namespace CLEYERA
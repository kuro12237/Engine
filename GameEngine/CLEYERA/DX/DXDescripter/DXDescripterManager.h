#pragma once
#include "../../pch/Pch.h"

namespace CLEYERA {
namespace Base {
namespace DX {

class DXRTVDescripter;
class DXSRVDescripter;
class DXDSVDescripter;

/// <summary>
/// でスクリプタ管理クラス
/// </summary>
class DXDescripterManager {
 public:
   static DXDescripterManager *GetInstance() {
      static DXDescripterManager instance;
      return &instance;
   }

   size_t RTVAddPtr(ID3D12Resource *buf, D3D12_RENDER_TARGET_VIEW_DESC desc);
   void RTVRelease(size_t index);

   size_t SRVAddPtr();
   size_t SRVAddCreatePtr(ID3D12Resource *buf, D3D12_SHADER_RESOURCE_VIEW_DESC desc);
   size_t UAVAddPtr(ID3D12Resource *buf, D3D12_UNORDERED_ACCESS_VIEW_DESC desc);
   void SRV_UAVReleace(size_t index);

   size_t DSVAddPtr(ID3D12Resource *buf, D3D12_DEPTH_STENCIL_VIEW_DESC desc);
   void DSVRelease(size_t index);

#pragma region Get

   std::weak_ptr<DXSRVDescripter> GetSRV() { return srvDescripter_; }
   D3D12_CPU_DESCRIPTOR_HANDLE GetSRVCPUHandle(size_t index);
   D3D12_GPU_DESCRIPTOR_HANDLE GetSRVGPUHandle(size_t index);
   D3D12_CPU_DESCRIPTOR_HANDLE GetRTVCPUHandle(size_t index);
   D3D12_CPU_DESCRIPTOR_HANDLE GetDSVCPUHandle(size_t index);

   ID3D12Resource *GetRTVResource(size_t index);


#pragma endregion

#pragma region Set
   void SetRTVDescripter(std::weak_ptr<DXRTVDescripter> rtv) { rtvDescripter_ = rtv; }
   void SetSRVDescripter(std::weak_ptr<DXSRVDescripter> srv) { srvDescripter_ = srv; }
   void SetDSVDescripter(std::weak_ptr<DXDSVDescripter> dsv) { dsvDescripter_ = dsv; }
#pragma endregion

 private:
   std::weak_ptr<DXRTVDescripter> rtvDescripter_;
   std::weak_ptr<DXSRVDescripter> srvDescripter_;
   std::weak_ptr<DXDSVDescripter> dsvDescripter_;

   DXDescripterManager() = default;
   ~DXDescripterManager() = default;
   DXDescripterManager(const DXDescripterManager &) = delete;
   DXDescripterManager &operator=(const DXDescripterManager &) = delete;
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA
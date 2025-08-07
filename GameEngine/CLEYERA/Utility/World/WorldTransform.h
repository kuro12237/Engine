#pragma once

#include "../../DX/DXManager.h"
#include "../../WIn/WinApp.h"
#include "../../pch/Pch.h"
#include "../TransformBase/TransformBase.h"

#include "../Camera/CameraManager.h"

namespace CLEYERA {
namespace Util {

/// <summary>
/// ワールド
/// </summary>
class WorldTransform : public TransformBase {
 public:
   WorldTransform() {};
   virtual ~WorldTransform() {};

   void WTCreate(const uint32_t &instanceNum);
   void ConvertMat();

   void SetWorldTransfar();

   void BindWT(UINT num);

 private:

 protected:
   std::shared_ptr<Base::DX::DXBufferResource<system::forWorldMat>> buf_ = nullptr;
   const system::SCamera *camera_ = nullptr;

   // ras
   system::forWorldMat forGpuWorldMat_ = {};
   const uint32_t *instanceNum_ = nullptr;
};

} // namespace Util
} // namespace CLEYERA

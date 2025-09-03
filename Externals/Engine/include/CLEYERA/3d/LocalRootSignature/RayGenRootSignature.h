#pragma once

#include "../../DX/DXManager.h"

namespace CLEYERA {
namespace Model3d {
namespace system {

/// <summary>
/// RayGenのルートシグネチャ
/// </summary>
class RayGenRootSignature {
 public:
   RayGenRootSignature() {};
   ~RayGenRootSignature() {};

   void Create();

#pragma region Get

   ComPtr<ID3D12RootSignature >GetRootSignature() { return rootSignature_; }

#pragma endregion

 private:
   ComPtr<ID3D12RootSignature> rootSignature_ = nullptr;
};

} // namespace system
} // namespace Model3d
} // namespace CLEYERA
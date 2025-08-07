#pragma once
#include "../../DX/DXManager.h"

namespace CLEYERA {
namespace Model3d {
namespace system {

/// <summary>
/// CloseHitのルートシグネチャ
/// </summary>
class CloseHitRootSignature {
 public:
   CloseHitRootSignature() {};
   ~CloseHitRootSignature() {};

   void Create();

   #pragma region Get

   ID3D12RootSignature *GetRootSignature() { return rootSignature_.Get(); }

#pragma endregion

 private:
   ComPtr<ID3D12RootSignature> rootSignature_ = nullptr;
};

} // namespace system
} // namespace Model3d
} // namespace CLEYERA
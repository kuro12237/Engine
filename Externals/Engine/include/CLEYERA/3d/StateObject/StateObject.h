#pragma once
#include "../../DX/DXManager.h"
#include "../../Graphics/ShaderManager/ShaderManager.h"
#include "../../pch/Pch.h"

#include "../../Graphics/RaytracingManager/HitGroup.h"

namespace CLEYERA {
namespace Model3d {
namespace system {

/// <summary>
///
/// </summary>
class PiplineStateObject {
 public:
   PiplineStateObject() {};
   ~PiplineStateObject() {};

   void Init();

#pragma region Set
   void SetClosetHitRootSignature(ID3D12RootSignature *r) { closetHitRootSignature_ = r; }
   void SetRayGenRootSignature(ComPtr<ID3D12RootSignature> r) { rayGenRootSignature_ = r; }

   void SetGlobalRootSignature(ID3D12RootSignature* r) { globalRootSignature_ = r; }
#pragma endregion

#pragma region get
   ComPtr<ID3D12StateObject> GetStateObject() { return stateObject_; }

#pragma endregion

 private:
   ID3D12RootSignature *globalRootSignature_ = nullptr;
   ID3D12RootSignature *closetHitRootSignature_ = nullptr;

   ComPtr<ID3D12RootSignature> rayGenRootSignature_ = nullptr;
   ID3D12Device5 *device_ = nullptr;

   Microsoft::WRL::ComPtr<ID3D12StateObject> stateObject_;
};

} // namespace system
} // namespace Model3d
} // namespace CLEYERA
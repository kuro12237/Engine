#pragma once
#include "../../DX/DXBarrier/DXBarrier.h"
#include "../../DX/DXManager.h"
#include "../../pch/Pch.h"

namespace CLEYERA {
namespace Model3d {
namespace system {

class GlobalRootSignature {
 public:
   GlobalRootSignature() {};
   ~GlobalRootSignature() {};

   void Init();

   void Render();

   #pragma region Get
   ID3D12RootSignature *GetRootSignature() { return rootSignature_.Get(); }

#pragma endregion


 private:
   Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_;
};

} // namespace system
} // namespace Model3d
} // namespace CLEYERA
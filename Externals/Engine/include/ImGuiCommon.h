#pragma once

#include "../../DX/DXBufferResource/DXBufferResource.h"
#include "../../DX/DXManager.h"
#include "../../WIn/WinApp.h"
#include "../../pch/Pch.h"

namespace CLEYERA {

namespace Utility {

/// <summary>
/// ImGui管理クラス
/// </summary>
class ImGuiCommon {
 public:
   ImGuiCommon();
   ~ImGuiCommon();

   void Init();

   void Begin();

   void Render();

   void End();

 private:
   Base::Win::WinApp *winApp_ = nullptr;
   Base::DX::DXManager *dxManager_ = nullptr;
   Base::DX::DXDescripterManager *descripterManager_ = nullptr;

   ID3D12GraphicsCommandList *commandList_ = nullptr;

   size_t srvIndex_ = 0;
};
} // namespace Utility
} // namespace CLEYERA
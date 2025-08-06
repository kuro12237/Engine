#pragma once

#include "ImGuiCommon.h"

namespace CLEYERA {

namespace Utility {

/// <summary>
/// ImGui管理クラス
/// </summary>
class ImGuiManager {
 public:
   static ImGuiManager *GetInstance();

   void Init();

   void Begin();

   void Render();
   
   void End();

   void SetImGuiCommon(std::weak_ptr<ImGuiCommon> common) { common_ = common; }

#pragma region Ui

   void BeginParamsList();

   void EndParamsList();

#pragma endregion

 private:
   std::weak_ptr<ImGuiCommon> common_;

   ImGuiManager() = default;
   ~ImGuiManager() = default;
   ImGuiManager(const ImGuiManager &) = delete;
   ImGuiManager &operator=(const ImGuiManager &) = delete;
};
} // namespace Utility
} // namespace CLEYERA

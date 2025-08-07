#include "ImGuiManager.h"

namespace CLEYERA {

namespace Utility {

ImGuiManager *CLEYERA::Utility::ImGuiManager::GetInstance() {
   static ImGuiManager instance;
   return &instance;
}

void ImGuiManager::Init() { common_.lock()->Init(); }

void ImGuiManager::Begin() { common_.lock()->Begin(); }

void ImGuiManager::Render() { common_.lock()->Render(); }

void ImGuiManager::End() { common_.lock()->End(); }

void ImGuiManager::BeginParamsList() {

   ImGui::SetNextWindowPos(ImVec2(1280-320, 0), ImGuiCond_Always);
   ImGui::SetNextWindowSize(ImVec2(320, 720), ImGuiCond_Always);
   ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
   ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.02f, 0.02f, 0.02f, 1.0f));
   ImGui::Begin("Params", nullptr, ImGuiWindowFlags_NoCollapse);
}

void ImGuiManager::EndParamsList() {
   ImGui::End();
   ImGui::PopStyleColor();
   ImGui::PopStyleColor();
}

} // namespace Utility
} // namespace CLEYERA
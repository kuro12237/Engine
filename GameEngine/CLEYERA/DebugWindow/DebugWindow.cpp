#include"DebugWindow.h"
#include"../Utility/ImGui/ImGuiManager.h"



namespace CLEYERA {

namespace DebugTools {

void DebugWindow::Init() {



};

void DebugWindow::Update() {

    if (ImGui::BeginMainMenuBar()) {

    if (ImGui::BeginMenu("設定")) {
      ImGui::MenuItem("項目 A");
      ImGui::MenuItem("項目 B");
      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }

  if (ImGui::BeginTabBar("MyTabBar")) {
    if (ImGui::BeginTabItem("タブ1")) {
      ImGui::Text("タブ1の内容");
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("タブ2")) {
      ImGui::Text("タブ2の内容");
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("タブ3")) {
      ImGui::Text("タブ3の内容");
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }
}

}
} // namespace CLEYERA
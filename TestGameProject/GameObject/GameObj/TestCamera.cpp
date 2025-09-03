#include "TestCamera.h"

void TestCamera::Init() {
  this->name_ = VAR_NAME(TestCamera);
  //この関数を呼び出すとこのカメラからの描画に変わる
  this->CameraChange();
  translate_.y = 2.0f;
}

void TestCamera::Update() {

#ifdef _DEBUG

  if(ImGui::TreeNode("TestCamera")) {
    ImGui::DragFloat3("rotate", &rotate_.x);
    ImGui::DragFloat3("translate", &translate_.x);

    ImGui::TreePop();
  }

#endif // _DEBUG
}

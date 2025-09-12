#include "TestScene.h"

void TestScene::Init() {

  auto objManager = CLEYERA::Manager::ObjectManager::GetInstance();

  objManager->LoadObjectData("test.json");

  testObj_.resize(4);

  testObj_[0] = objManager->CreateObject<TestObj>(VAR_NAME(TestObj),
                                                  std::make_shared<TestObj>());

  testObj_[1] = objManager->CreateObject<TestObj>(VAR_NAME(TestObj),
                                                  std::make_shared<TestObj>());
  num_ = 1;
  testCamera_ = std::make_shared<TestCamera>();
  testCamera_->Init();

  testSprite_ = std::make_unique<TestSprite>();
  testSprite_->Init();
}

void TestScene::Update(CLEYERA::Manager::SceneManager *ins) {
  ins;
  auto objManager = CLEYERA::Manager::ObjectManager::GetInstance();

#ifdef _DEBUG

  if (ImGui::TreeNode("Push")) {

    if (ImGui::Button("new")) {

      num_++;
      testObj_[num_] = objManager->CreateObject<TestObj>(
          VAR_NAME(TestObj), std::make_shared<TestObj>());
    }
    if (ImGui::Button("Delete")) {

      testObj_[num_].lock()->SetMode(
          CLEYERA::Component::ObjectComponent::OBJ_MODE::REMOVE);
      num_--;
    }
    ImGui::TreePop();
  }

#endif // _DEBUG

  testCamera_->Update();
  testSprite_->Update();
}

void TestScene::Draw2d() { testSprite_->Draw(); }

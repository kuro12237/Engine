#include "TestScene.h"

uint32_t modelHandle = 0;
void TestScene::Init() {

  auto objManager = CLEYERA::Manager::ObjectManager::GetInstance();

  objManager->LoadObjectData("test.json");

  testObj_.resize(128);
  std::string category = VAR_NAME(TestObj);
  modelHandle = CLEYERA::Manager::ModelManager::GetInstance()->LoadModel(
      "Resources/Model/system/NormalBox", "NormalBox");
  objManager->GetCategoryData(category).ChangeModelData(modelHandle);
  objManager->GetCategoryData(category).ChangeDrawMode(
      CLEYERA::Graphics::RasterPipline_Mode3d::Normal_MODEL3d);

  num_ = 1;
  testCamera_ = std::make_shared<TestCamera>();
  testCamera_->Init();

  testSprite_ = std::make_unique<TestSprite>();
  testSprite_->Init();

     for (size_t i = 0; i < 999; i++) {

    auto obj = objManager->CreateObject<TestObj>(VAR_NAME(TestObj),
                                                 std::make_shared<TestObj>());
    obj.lock()->SetPos(this->GenerateSpawnPos());
  }
}

void TestScene::Update(CLEYERA::Manager::SceneManager *ins) {
  ins;
  auto objManager = CLEYERA::Manager::ObjectManager::GetInstance();

  spawnInterval_ += 1.0f / 60.0f;

  if (spawnInterval_ >= 1.0f) {

   
    spawnInterval_ = 0.0f;
  }

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

void TestScene::Draw2d() { // testSprite_->Draw();
}

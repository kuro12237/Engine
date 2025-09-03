#include "TestScene.h"

void TestScene::Init() {

  auto objManager = CLEYERA::Manager::ObjectManager::GetInstance();
  auto cameraManager = CLEYERA::Manager::CameraManager::GetInstance();

  testObj_ = objManager->CreateObject<TestObj>(VAR_NAME(TestObj),
                                               std::make_shared<TestObj>());

  testCamera_ = std::make_shared<TestCamera>();
  testCamera_->Init();

  testSprite_ = std::make_unique<TestSprite>();
  testSprite_->Init();
}

void TestScene::Update(CLEYERA::Manager::SceneManager *ins) {
  ins;

  testCamera_->Update();
  testSprite_->Update();
}

void TestScene::Draw2d() { testSprite_->Draw(); }

#pragma once
#include "CLEYERA.h"

#include "GameObj/TestObject.h"
#include"GameObj/TestCamera.h"
#include"GameObj/TestSprite.h"

class TestScene : public CLEYERA::Component::SceneComponent {
public:
  TestScene() {};
  ~TestScene() {};

  void Init() override;
  void Update(CLEYERA::Manager::SceneManager *ins) override;
  void Draw2d();


private:
  std::vector<std::weak_ptr<TestObj>> testObj_;

  std::shared_ptr<TestCamera> testCamera_ = nullptr;
  std::unique_ptr<TestSprite> testSprite_ = nullptr;

  int num_ = 0;

};
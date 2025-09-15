#pragma once
#include "CLEYERA.h"

#include "GameObj/TestCamera.h"
#include "GameObj/TestObject.h"
#include "GameObj/TestSprite.h"

class TestScene : public CLEYERA::Component::SceneComponent {
public:
  TestScene() {};
  ~TestScene() {};

  void Init() override;
  void Update(CLEYERA::Manager::SceneManager *ins) override;
  void Draw2d();

private:
  Math::Vector::Vec3 GenerateSpawnPos() {
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_real_distribution<float> dist(-50.0f, 50.0f);

    float x = dist(rng);
    float z = dist(rng);
    return {x, 0.0f, z};
  }

  std::vector<std::weak_ptr<TestObj>> testObj_;

  std::shared_ptr<TestCamera> testCamera_ = nullptr;
  std::unique_ptr<TestSprite> testSprite_ = nullptr;

  int num_ = 0;

  float spawnInterval_ = 0.36f;
};
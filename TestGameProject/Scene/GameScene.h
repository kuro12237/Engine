#pragma once

#include "CLEYERA.h"

#include "../gameObject/Player/PlayerManager.h"
#include "../GameObject/Sun/Sun.h"
#include"../Util/SceneLoader.h"

#include"../GameObject/Block/BlockManager.h"

class GameScene : public CLEYERA::Component::SceneComponent {
public:
  GameScene() {};
  ~GameScene() {};

  void Init() override;
  void Update(CLEYERA::Manager::SceneManager *ins) override;

private:
  std::unique_ptr<Sun> sun_ = nullptr;
  std::unique_ptr<PlayerManager> player_ = nullptr;
  std::unique_ptr<BlockManager> blocks_ = nullptr;

  std::unique_ptr<SceneLoader> loader_ = nullptr;
};
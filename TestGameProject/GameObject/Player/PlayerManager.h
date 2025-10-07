#pragma once
#include "Camera/PlayerCamera.h"
#include "PlayerCore/PlayerCore.h"

#include"PlayerCore/Command/PlayerCommandHandler.h"

class PlayerManager {
public:
  PlayerManager() {};
  ~PlayerManager() {};

  void Init();

  void Update();

private:
  std::weak_ptr<PlayerCore> core_;
  std::unique_ptr<PlayerCamera> camera_ = nullptr;

  std::unique_ptr<PlayerCommandHandler> commandHandler_ = nullptr;
};
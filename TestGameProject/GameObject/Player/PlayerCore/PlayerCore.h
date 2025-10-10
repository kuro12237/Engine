#pragma once
#include "../Base/IPlayer.h"
#include "CLEYERA.h"

#include "Command/IPlayerCommand.h"

#include"../../Block/DFBlock/NormalBlock.h"

class PlayerCore : public IPlayer {
public:
  PlayerCore() {};
  ~PlayerCore() {};

  void Init() override;

  void Update() override;

  void OnCollision(std::weak_ptr<CLEYERA::Component::ObjectComponent>other);

#pragma region Command

  /// <summary>
  /// 移動コマンド
  /// </summary>
  void MoveCommand();

  void JumpCommand();

#pragma endregion

private:

  float speed_ = 0.1f;
  std::queue<CLEYERA::Util::Collider::HitDirection> prev_;

};

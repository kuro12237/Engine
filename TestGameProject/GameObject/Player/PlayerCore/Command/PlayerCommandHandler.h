#pragma once
#include "CLEYERA.h"
#include "IPlayerCommand.h"

#include "PlayerCommandMove.h"
#include "PlayerJumpCommand.h"

class PlayerCommandHandler {
public:
  PlayerCommandHandler() {};
  ~PlayerCommandHandler() {};

  /// <summary>
  /// コマンド実行
  /// </summary>
  void ExeCommands();

  /// <summary>
  /// こまんどチェック
  /// </summary>
  void InputCheckCommand();

  void SetPlayer(const std::weak_ptr<PlayerCore> &p) { player_ = p; }

private:
  std::queue<std::unique_ptr<IPlayerCommand>> commands_;
  std::weak_ptr<PlayerCore> player_;
};
#pragma once
#include"IPlayerCommand.h"
#include"../PlayerCore.h"


class PlayerCommandMove :public IPlayerCommand{
public:
  PlayerCommandMove() {};
  ~PlayerCommandMove() {};

  void Execute(PlayerCore *p);

private:
};
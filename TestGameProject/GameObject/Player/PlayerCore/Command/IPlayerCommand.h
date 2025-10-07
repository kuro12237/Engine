#pragma once

class PlayerCore;
class IPlayerCommand {
public:
  IPlayerCommand() {};
  virtual ~IPlayerCommand() {};

  virtual void Execute(PlayerCore *p) = 0;

private:
};

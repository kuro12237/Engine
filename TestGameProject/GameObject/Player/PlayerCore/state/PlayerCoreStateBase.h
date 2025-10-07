#pragma once

class PlayerCore;

class PlayerCoreStateBase {
public:
  PlayerCoreStateBase() {};
  virtual ~PlayerCoreStateBase() {};

  virtual void Init() {};

  virtual void Update(PlayerCore *p) {};

protected:
  bool isCommandActive_ = false;

private:
};

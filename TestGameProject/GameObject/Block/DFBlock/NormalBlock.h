#pragma once
#include"../Base/BlockBase.h"

/// <summary>
/// 通常ブロック
/// </summary>
class NormalBlock :public BlockBase{
public:
  NormalBlock() {};
  ~NormalBlock() {};

  void Init() override;

  void Update() override;
  void OnCollision(std::weak_ptr<ObjectComponent> other) override {};

private:
};

#pragma once
#include "Game3dObject.h"

namespace CLEYERA {

namespace Model3d {

class InstancingGameObject {
public:
  InstancingGameObject() {};
  ~InstancingGameObject() {};

  void Init(uint32_t max = 1);

  void Update();

  void Command(uint32_t num);

  void
  SetWorldData(const CLEYERA::Util::system::forWorldMat *data,uint32_t index) {
    worldMat_[index] = data;
  }

  void DelateData(uint32_t index) { worldMat_[index] = nullptr;
  }

private:
  std::unique_ptr<
      CLEYERA::Base::DX::DXBufferResource<CLEYERA::Util::system::forWorldMat>>
      buf_ = nullptr;
  std::vector<const CLEYERA::Util::system::forWorldMat*> worldMat_;
};

} // namespace Model3d
} // namespace CLEYERA
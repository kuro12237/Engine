#pragma once
#include "InstancingBase.h"

namespace CLEYERA {

namespace Model3d {

class InstancingWorld :public InstancingBase<CLEYERA::Util::system::forWorldMat>{
public:
  InstancingWorld() {};
  ~InstancingWorld() {};

  void Init(uint32_t max = 1)override;

  void Update()override;


private:
};

} // namespace Model3d
} // namespace CLEYERA
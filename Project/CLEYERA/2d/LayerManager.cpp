#include "LayerManager.h"

uint32_t CLEYERA::Sprite2d::System::LayerManager::RegisterLayer(uint32_t &layerNum) {

    //ポインタ登録
  layerMap_.push_back(&layerNum);

  uint32_t result = 0;
  if (!poolMap_.empty()) {

    uint32_t num = poolMap_.front();
    poolMap_.pop();

    result = num;
  } else {

    result = count_;
    count_++;
  }

  return result;
}

void CLEYERA::Sprite2d::System::LayerManager::RemoveLayer(uint32_t num) {

  this->poolMap_.push(num);
}

void CLEYERA::Sprite2d::System::LayerManager::ChangeLayer(uint32_t prevNum, uint32_t newNum) {

  for (auto &obj : layerMap_) {
    if (*obj == prevNum) {
      *obj = newNum;
    } else if (*obj == newNum) {
      *obj = prevNum;
    }
  }
}

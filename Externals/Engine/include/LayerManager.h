#pragma once

#include"../pch/Pch.h"

namespace CLEYERA {

namespace Sprite2d {

namespace System {

class LayerManager {
public:

	static LayerManager *GetInstance() {
    static LayerManager ins;
    return &ins;
  };

  [[nodiscard]] uint32_t RegisterLayer(uint32_t &layerNum);

  void RemoveLayer(uint32_t num);

  void ChangeLayer(uint32_t prevNum, uint32_t newNum);

private:
  std::list<uint32_t *> layerMap_;
  std::queue<uint32_t> poolMap_;
  std::int32_t count_ = 0;



  LayerManager() = default;
  ~LayerManager() = default;
  LayerManager(const LayerManager &) = delete;
  const LayerManager &operator=(const LayerManager &) = delete;
};

} // namespace System
} // namespace Sprite2d
} // namespace CLEYERA
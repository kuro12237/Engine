#pragma once
#include "../Object/ObjectManager.h"
#include "PostEffect/PostEffect.h"

namespace CLEYERA {

namespace Manager {

class RenderManager {
public:
  RenderManager() {};
  ~RenderManager() {};

  void Init();

  void Update();

  void Draw3d();

  void PreDraw();
  void PostDraw();
  void PostEffectDraw();

private:

    D3D12_GPU_DESCRIPTOR_HANDLE GetHandle(uint32_t handle);

  const std::map<
      std::string,
      std::map<std::string, std::shared_ptr<Component::ObjectComponent>>>
      *objects_ = nullptr;
  const std::map<std::string, Util::system::InstancingObjectData>
      *instancingData_ = nullptr;

  CLEYERA::Manager::PostEffectManager *postEffect_;
};

} // namespace Manager

} // namespace CLEYERA

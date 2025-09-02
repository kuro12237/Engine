#pragma once
#include "Compornent/SceneComponent.h"
#include "pch/Pch.h"

namespace CLEYERA {
namespace Manager {

class SceneManager {
public:
  static SceneManager *GetInstance() { static SceneManager instance; 
  return &instance;
  }
  void Init();
  void Update();
  void ImGuiUpdate();
  void Draw2d();

  //using SceneFactoryFunc =
  //    std::function<std::unique_ptr<CLEYERA::Component::SceneComponent>()>;

  //template <typename T> void RegisterScene(const std::string &name);

  void ChangeScene(const std::string &name);

private:
  //std::unordered_map<std::string, SceneFactoryFunc> sceneFactoryMap_;
  std::unique_ptr<CLEYERA::Component::SceneComponent>currentScene_;

  SceneManager() = default;
  ~SceneManager() = default;
  SceneManager(const SceneManager &) = delete;
  const SceneManager &operator=(const SceneManager &) = delete;
};

//template <typename T>
//void SceneManager::RegisterScene(const std::string &name) {
//  static_assert(std::is_base_of<CLEYERA::Component::SceneComponent, T>::value, "T must derive from IScene");
//  //sceneFactoryMap_[name] = []() { return std::make_unique<T>(); };
//}

} // namespace Manager
} // namespace CLEYERA
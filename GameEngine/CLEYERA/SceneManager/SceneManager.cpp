#include "SceneManager.h"

using namespace CLEYERA::Manager;

void CLEYERA::Manager::SceneManager::Init() {}

void CLEYERA::Manager::SceneManager::Update() {
  if (currentScene_) {
  }
    //currentScene_->Update(this);
}

void CLEYERA::Manager::SceneManager::ImGuiUpdate() {
  if (currentScene_)
    currentScene_->ImGuiUpdate();
}

void CLEYERA::Manager::SceneManager::Draw2d() {
  if (currentScene_)
    currentScene_->Draw2d();
}

void CLEYERA::Manager::SceneManager::ChangeScene(const std::string &name) {

  //auto it = sceneFactoryMap_.find(name);
  //if (it != sceneFactoryMap_.end()) {
  //  if (currentScene_)
  //    currentScene_->Finalize();

  //  currentScene_ = it->second(); // シーン生成

  //  if (currentScene_)
  //    currentScene_->Init();
  //}
}

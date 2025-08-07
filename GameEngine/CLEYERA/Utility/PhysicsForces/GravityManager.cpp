#include "GravityManager.h"

void CLEYERA::Manager::GravityManager::Init() {}

void CLEYERA::Manager::GravityManager::Update() {

  for (auto it = objs_.begin(); it != objs_.end();) {
    if (it->expired()) {
      it = objs_.erase(it); // イテレータを更新
    } else {
      it->lock()->GravityUpdate(gravity_);
      ++it;
    }
  }
}

void CLEYERA::Manager::GravityManager::RemoveData() {}

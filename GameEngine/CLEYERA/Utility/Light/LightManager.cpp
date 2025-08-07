#include "LightManager.h"

void CLEYERA::Manager::LightManager::Init() {

	directionLight_ = std::make_shared<DirectionLight>();
   directionLight_->Init();

}

void CLEYERA::Manager::LightManager::Update() { directionLight_->Update(); }

void CLEYERA::Manager::LightManager::ImGuiUpdate() {

directionLight_->ImGuiUpdate();

}

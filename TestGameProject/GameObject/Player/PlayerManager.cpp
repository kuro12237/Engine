#include "PlayerManager.h"

void PlayerManager::Init() {

  camera_ = std::make_unique<PlayerCamera>();
  camera_->Init();

  auto objM = CLEYERA::Manager::ObjectManager::GetInstance();
  core_ = objM->CreateObject<PlayerCore>(VAR_NAME(PlayerCore),
                                         std::make_shared<PlayerCore>());

  commandHandler_ = std::make_unique<PlayerCommandHandler>();
  commandHandler_->SetPlayer(core_);

  camera_->SetPlayerPos(&core_.lock()->GetTranslate());
}

void PlayerManager::Update() {

  commandHandler_->InputCheckCommand();
  commandHandler_->ExeCommands();

  camera_->Update();
}
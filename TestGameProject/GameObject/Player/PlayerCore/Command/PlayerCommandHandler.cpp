#include "PlayerCommandHandler.h"

void PlayerCommandHandler::ExeCommands() {

  if (player_.expired()) {
    return;
  }

  while (!commands_.empty()) {
    auto &c = commands_.front();
    c->Execute(player_.lock().get());
    commands_.pop();
  }
}

void PlayerCommandHandler::InputCheckCommand() {

  CLEYERA::Manager::InputManager *input =
      CLEYERA::Manager::InputManager::GetInstance();

  if (input->IsLJoystickActive()) {

    commands_.push(std::make_unique<PlayerCommandMove>());
  }
  if (input->PushBottonPressed(XINPUT_GAMEPAD_A)) {

    commands_.push(std::make_unique<PlayerCommandJump>());
  }
}

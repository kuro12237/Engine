#include "SystemLogManager.h"

using namespace CLEYERA::LogManager;

SystemLogManager::SystemLogManager() {

  logFile_.open(this->fileName_, std::ios::app);

  if (logFile_.is_open()) {
    logFile_ << "Create " + fileName_ << std::endl;
  }
}

void SystemLogManager::OnObjectCreated(const std::string &objectType) {

  std::string output = "[LOG] Created: " + objectType;
  Log(output);
}

void CLEYERA::LogManager::SystemLogManager::OnMsg(const std::string &msg) 
{
  Log(msg);
}


void SystemLogManager::Log(const std::string &message) {
  std::string outmes = message + "\n";
  OutputDebugStringA(outmes.c_str());
  if (logFile_.is_open()) {

    logFile_ << message << std::endl;
  }

}

SystemLogManager::~SystemLogManager() {
  if (logFile_.is_open()) {
    logFile_.close();
  }
}
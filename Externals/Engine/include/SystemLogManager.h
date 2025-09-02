#pragma once
#include "ISystemObserver.h"
#include"ConvertString.h"

namespace CLEYERA {
namespace LogManager {

class SystemLogManager : public CLEYERA::LogManager::ISystemObserver {
public:
  SystemLogManager();
  ~SystemLogManager();

  /// <summary>
  ///
  /// </summary>
  /// <param name="objectType"></param>
  void OnObjectCreated(const std::string &objectType) override;

  void OnMsg(const std::string &msg) override;

  void Log(const std::string &message);

private:
  std::string fileName_ = "BuildLog.txt";
  std::ofstream logFile_;
};

} // namespace LogManager
} // namespace CLEYERA
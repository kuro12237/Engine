#pragma once
#include "../pch/Pch.h"

namespace CLEYERA {
namespace LogManager {

/// <summary>
///
/// </summary>
class ISystemObserver {
public:
  ISystemObserver() = default;
  virtual ~ISystemObserver() = default;

  virtual void OnObjectCreated(const std::string &objectType) = 0;

  virtual void OnMsg(const std::string &msg) = 0;

private:
};
} // namespace LogManager
} // namespace CLEYERA
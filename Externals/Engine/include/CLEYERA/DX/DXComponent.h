#pragma once
#include "../SystemLogManager/ISystemObserver.h"
#include"../WIn/WinApp.h"

namespace CLEYERA {
namespace Base {
namespace DX {

class DXManager;

/// <summary>
///
/// </summary>
class DXComponent {
public:
  DXComponent(const std::string &name) : name_(name) {};

  ~DXComponent() = default;

  virtual void Create() = 0;

  void AddObserver(
      const std::weak_ptr<CLEYERA::LogManager::ISystemObserver> &observer) {
    obsrvers_.push_back(observer);
  }

  void NotifyObserversCreateComp() {
    for (auto observer : obsrvers_) {
      observer.lock()->OnObjectCreated(name_);
    }
  }

  void NotifyObservesMsg(const std::string &m) {
    for (auto observer : obsrvers_) {
      observer.lock()->OnMsg(m);
    }
  }

private:
protected:
  std::string name_ = "";

  std::vector<std::weak_ptr<CLEYERA::LogManager::ISystemObserver>> obsrvers_;

  DXManager *dxManager_ = nullptr;
  CLEYERA::Base::Win::WinApp *winApp_ = nullptr;
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA

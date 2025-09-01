#pragma once

#include "pch/Pch.h"

#include "../Compornent/CameraCompornent.h"
#include "ObjectCompornent.h"

#include "../Utility/Object/ObjectManager.h"

namespace CLEYERA {

namespace Component {

class ManagerComponent {
public:
  ManagerComponent() {
    colliderSystem_ = Manager::ColliderSystem::GetInstance();
    objectManager_ = Manager::ObjectManager::GetInstance();
  };
  virtual ~ManagerComponent() {};

  virtual void Init() = 0;

  virtual void Update() = 0;

  virtual void ImGuiUpdate();

  void CollectAllManagers();

#pragma region Get

  std::list<std::weak_ptr<Component::ManagerComponent>> &GetManagerList() {
    return childManagerComponents_;
  }

#pragma endregion

private:
protected:
  Manager::ColliderSystem *colliderSystem_ = nullptr;
  Manager::ObjectManager *objectManager_ = nullptr;

  void ListInit();
  void ListUpdate();

  std::string name_ = "";

  std::list<std::weak_ptr<Component::CameraCompornent>> cameraComponents_;

  std::list<std::weak_ptr<Component::ManagerComponent>>
      childManagerComponents_;
};

} // namespace Component

} // namespace CLEYERA

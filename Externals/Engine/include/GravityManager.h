#pragma once
#include "Compornent/ObjectCompornent.h"

namespace CLEYERA {

namespace Manager {

/// <summary>
/// 重力
/// </summary>
class GravityManager {
 public:
   static GravityManager *GetInstance() {
      static GravityManager ins;
      return &ins;
   }

   void Init();

   void Update();

   void PushData(std::weak_ptr<Component::ObjectComponent> obj) { objs_.push_back(obj); };

   void RemoveData();

   void Clear() { return objs_.clear(); }

 private:
   std::list<std::weak_ptr<Component::ObjectComponent>> objs_;

   float gravity_ = -0.1f;

#pragma region Singleton

   GravityManager() = default;
   ~GravityManager() = default;
   GravityManager(const GravityManager &) = delete;
   GravityManager &operator=(const GravityManager &) = delete;

#pragma endregion
};

} // namespace Manager
} // namespace CLEYERA
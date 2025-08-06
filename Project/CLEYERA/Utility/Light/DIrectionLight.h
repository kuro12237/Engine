#pragma once
#include "DX/DXManager.h"

namespace CLEYERA {

namespace Graphics {
namespace system {

struct SDirectionLight {

   Math::Vector::Vec4 color = {1.0f, 1.0f, 1.0f,1.0f};
   Math::Vector::Vec3 direction = {0.0f, -1.0f, 0.0f};
   float intencity = 1.0f;
};
} // namespace system
} // namespace Graphics


namespace Manager {

   /// <summary>
   /// 平行光源
   /// </summary>
   class DirectionLight {
    public:
      DirectionLight() {};
      ~DirectionLight() {};

      void Init();

      void Update();

      void ImGuiUpdate();

      void CommandBind(UINT num);

    private:
      std::unique_ptr<Base::DX::DXBufferResource<Graphics::system::SDirectionLight>> buf_ =nullptr;
      Graphics::system::SDirectionLight light_;
      Base::DX::DXCommandManager *commandManager_ = nullptr;
   };

} // namespace Manager
} // namespace CLEYERA
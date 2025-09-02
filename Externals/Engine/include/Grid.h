#pragma once
#include "../3d/Game3dObject.h"
#include "../3d/Line3d/Line3d.h"
#include"../Utility/RenderManager/RenderManager.h"

namespace CLEYERA {

namespace DebugTools {

class Grid {
 public:

	 static Grid *GetInstance() {
      static Grid instance;
      return &instance;
   }

   void Init();

   void Update();

   void ImGuiUpdate();

   void DrawRaster3d();

   void Finalize();

 private:
   bool isUse_ = true;

   const std::string planePath_ = "Resources/Model/system/DebugPlane";
   const std::string planeName_ = "DebugPlane";
   std::shared_ptr<CLEYERA::Model3d::Game3dObject> grid_ = nullptr;

   Math::Vector::Vec3 scale_ = {1.0f, 1.0f, 1.0f};
   Math::Vector::Vec3 rotate_ = {};
   Math::Vector::Vec3 translate_ = {0.0f, 0.0f, 0.0f};

   size_t lineMax_ = 128;
   size_t lineVertCount_ = 256;

   std::shared_ptr<CLEYERA::Model3d::Line3d> lines_ = nullptr;
   std::vector<Math::Vector::Vec3> positions_;
   std::vector<Math::Vector::Vec4> colors_;

#pragma region Singleton

   Grid() = default;
   ~Grid() = default;
   Grid(const Grid &) = delete;
   Grid &operator=(const Grid &) = delete;

#pragma endregion
};

} // namespace DebugTools
} // namespace CLEYERA
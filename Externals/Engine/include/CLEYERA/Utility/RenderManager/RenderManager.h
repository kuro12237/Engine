#pragma once
#include "../../3d/Game3dObject.h"
#include "../../3d/Line3d/Line3d.h"

#include "../../Graphics/RasterPipline/RasterPiplineManager.h"

#include "../Camera/CameraManager.h"

namespace CLEYERA {

namespace Manager {

/// <summary>
/// 表示の管理クラス
/// </summary>
class RenderManager {
 public:
   static RenderManager *GetInstance() {
      static RenderManager instance;
      return &instance;
   }

   void Init();

   void Update();

   void Draw3d();

   void PushObj(std::weak_ptr<Model3d::Game3dObject> obj) {
     objs_[obj.lock()->GetRasterMode()].push_back(obj);
   }

   void PushLine3d(std::weak_ptr<Model3d::Line3d> obj) { line3ds_.push_back(obj); }
 
   void PopLine3d(std::weak_ptr<Model3d::Line3d> line);

   void SetPipline(Graphics::PostEffect_Mode mode);

   void Clear() {
     this->objs_.clear();
     line3ds_.clear();
   }

 private:
  

   std::queue<std::weak_ptr<Model3d::Game3dObject>> newObjs_;

   std::map<Graphics::RasterPipline_Mode3d, std::list<std::weak_ptr<Model3d::Game3dObject>>> objs_;
   std::list < std::weak_ptr < Model3d::Line3d>> line3ds_;

   CameraManager *cameraManager_ = nullptr;
   CLEYERA::Graphics::Raster::RasterPiplineManager *piplineManager_ = nullptr;
   Base::DX::DXCommandManager *commandManager_ = nullptr;

#pragma region Singleton

   RenderManager() = default;
   ~RenderManager() = default;
   RenderManager(const RenderManager &) = delete;
   RenderManager &operator=(const RenderManager &) = delete;

#pragma endregion
};

} // namespace Manager

} // namespace CLEYERA

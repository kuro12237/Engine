#include "RenderManager.h"

void CLEYERA::Manager::RenderManager::Init() {
  commandManager_ = Base::DX::DXCommandManager::GetInstace();
  piplineManager_ =
      CLEYERA::Graphics::Raster::RasterPiplineManager::GetInstance();
  cameraManager_ = CLEYERA::Manager::CameraManager::GetInstance();
}

void CLEYERA::Manager::RenderManager::Update() {

  // 空の weak_ptr を削除
  for (auto &[mode, objList] : objs_) {
    objList.erase(
        std::remove_if(objList.begin(), objList.end(),
                       [](const std::weak_ptr<Model3d::Game3dObject> &obj) {
                         return obj.expired();
                       }),
        objList.end());
  }

  // knumに値があったらエラー
  if (!objs_[Graphics::RasterPipline_Mode3d::kNum].empty()) {
    assert(0);
  }
  if (!objs_[Graphics::RasterPipline_Mode3d::NONE].empty()) {
    assert(0);
  }
}

void CLEYERA::Manager::RenderManager::Draw3d() {

  for (size_t i = 1;
       i < static_cast<size_t>(Graphics::RasterPipline_Mode3d::kNum) - 1; i++) {

    piplineManager_->SetRootsignature(
        static_cast<Graphics::RasterPipline_Mode3d>(i));
    piplineManager_->SetPipline(static_cast<Graphics::RasterPipline_Mode3d>(i));

    for (auto obj : objs_[static_cast<Graphics::RasterPipline_Mode3d>(i)]) {
      auto it = obj.lock();
      if (it) {

        it->DrawRaster3d();
      }
    }
  }

  piplineManager_->SetRootsignature(Graphics::RasterPipline_Mode3d::LINE3d);
  piplineManager_->SetPipline(Graphics::RasterPipline_Mode3d::LINE3d);

  for (auto obj : line3ds_) {
    auto it = obj.lock();
    if (it) {

      // it->DrawLine3d();
    } else {
    }
  }
}

void CLEYERA::Manager::RenderManager::PopLine3d(
    std::weak_ptr<Model3d::Line3d> line) {

  // 有効な shared_ptr にロック
  auto linePtr = line.lock();
  if (!linePtr) {
    return; // 無効な weak_ptr の場合は何もしない
  }

  // line3ds_ リストから指定された Line3d オブジェクトを削除
  line3ds_.remove_if([&linePtr](const std::weak_ptr<Model3d::Line3d> &obj) {
    auto objPtr = obj.lock();
    return objPtr && objPtr == linePtr;
  });
}

#include "Grid.h"

void CLEYERA::DebugTools::Grid::Init() {

   uint32_t modelHandle = CLEYERA::Manager::ModelManager::GetInstance()->LoadModel(planePath_, planeName_);
   grid_ = std::make_shared<CLEYERA::Model3d::Game3dObject>();
   grid_->Create(modelHandle);
   grid_->SetScale(scale_);
   grid_->SetRotate(rotate_);
   grid_->SetTranslate(translate_);

   scale_ = {2.0f, 2.0f, 2.0f};
   //CLEYERA::Manager::RenderManager::GetInstance()->PushObj(grid_);

   lines_ = std::make_shared<CLEYERA::Model3d::Line3d>();
   lines_->Init(lineMax_);
   lines_->SetLinePos(positions_);
   lines_->SetLineColor(colors_);
   lines_->SetScale(scale_);
   lines_->SetRotate(rotate_);
   lines_->SetTranslate(translate_);

   positions_.resize(lineVertCount_);
   colors_.resize(lineVertCount_);

   //CLEYERA::Manager::RenderManager::GetInstance()->PushLine3d(lines_);
   int half = UINT(lineMax_) / 4;
   float spacing = 1.0f; // 線の間隔（必要に応じて変更）

   int index = 0;
   // 垂直線（X固定、Z変化）
   for (int i = -half; i < half; ++i) {
      float x = i * spacing;
      positions_[index++] = {x, 0.0f, -half * spacing}; // 始点（0）
      positions_[index++] = {x, 0.0f, half * spacing};  // 終点（1）
                                                        // 始点の色（赤）
   }

   // 水平線（Z固定、X変化）
   for (int i = -half; i < half; ++i) {
      float z = i * spacing;
      positions_[index++] = {-half * spacing, 0.0f, z}; // 始点（0）
      positions_[index++] = {half * spacing, 0.0f, z};  // 終点（1）
   }

   for (size_t i = 0; i < lineVertCount_; i += 2) {
      size_t lineIndex = i / 2;

      size_t halfLine = lineMax_ / 2;

      if (lineIndex == halfLine / 2) {
         // 垂直線の中心 (X=0)
         colors_[i] = {1.0f, 0.0f, 0.0f, 0.5f}; // 赤
         colors_[i + 1] = {1.0f, 0.0f, 0.0f, 0.5f};
      } else if (lineIndex == lineMax_ / 2 + halfLine / 2) {
         // 水平線の中心 (Z=0)
         colors_[i] = {0.0f, 0.0f, 1.0f, 0.5f}; // 青
         colors_[i + 1] = {0.0f, 0.0f, 1.0f, 0.5f};
      } else {
         colors_[i] = {0.6f, 0.6f, 0.6f, 0.5f};
         colors_[i + 1] = {0.6f, 0.6f, 0.6f, 0.5f};
      }
   }
}

void CLEYERA::DebugTools::Grid ::Update() {

   lines_->SetLinePos(positions_);
   lines_->Update();
   grid_->Update();
}

void CLEYERA::DebugTools::Grid::ImGuiUpdate() {

   ImGui::Begin("glines");

   for (size_t i = 0; i < positions_.size(); i++) {

      std::string name = "p" + std::to_string(i);
      ImGui::DragFloat3(name.c_str(), &positions_[i].x, 0.5f);
   }
   ImGui::End();
}

void CLEYERA::DebugTools::Grid::DrawRaster3d() { grid_->DrawRaster3d(); }

void CLEYERA::DebugTools::Grid::Finalize() {
   grid_.reset();
   lines_.reset();
}

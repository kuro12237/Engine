#pragma once
#include "../../Graphics/RasterPipline/RasterEnum.h"
#include "../../Utility/TransformBase/TransformBase.h"
#include "../../Utility/World/WorldTransform.h"
#include "../ModelManager/ModelManager.h"

namespace CLEYERA {

namespace Model3d {

class Line3d : public Util::WorldTransform {
 public:
   Line3d() {};
   ~Line3d() {};

   void Init(const size_t lineMax = 64);

   void Update();

   void DrawLine3d();

#pragma region Set
   void SetLinePos(const std::vector<Math::Vector::Vec3> &pos) { postions_ = &pos; }
   void SetLineColor(const std::vector<Math::Vector::Vec4> &color) { colors_ = &color; }
#pragma endregion

 private:
   Manager::CameraManager *cameraManager_ = nullptr;
   Base::DX::DXCommandManager *commandManager_ = nullptr;

   const size_t vertCount_ = 2;

   std::unique_ptr<MeshData> mesh_ = nullptr;

   std::unique_ptr<Base::DX::DXBufferResource<Math::Vector::Vec3>> lineBuf_ = nullptr;
   const std::vector<Math::Vector::Vec3> *postions_ = nullptr;

   std::unique_ptr<Base::DX::DXBufferResource<Math::Vector::Vec4>> lineColorBuf_ = nullptr;
   const std::vector<Math::Vector::Vec4> *colors_ = nullptr;

   size_t lineMax_ = 128;
};

} // namespace Model3d
} // namespace CLEYERA
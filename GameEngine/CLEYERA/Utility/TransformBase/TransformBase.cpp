#include "TransformBase.h"
#include "../../DX/DXManager.h"

using namespace Math::Vector;

CLEYERA::Util::TransformBase::TransformBase() {}

void CLEYERA::Util::TransformBase::WorldMatUpdate() {

   if (scale_ && rotate_ && translate_) {

      mat_ = Math::Matrix::Func::AffineMatrix(*scale_, *rotate_, *translate_);

      if (parent_.lock()) {
         mat_ = Math::Matrix::Func::Multiply(mat_, parent_.lock()->GetMat());

      }
   }
   forGpumat_.FromMat4x4(mat_);
}

void CLEYERA::Util::TransformBase::TransformImGuiUpdate() {

   if (ImGui::TreeNode("Transform")) {
      ImGui::DragFloat3("Scale", &scale_->x, 0.5f);
      ImGui::DragFloat3("Rotate", &rotate_->x, 0.5f);
      ImGui::DragFloat3("Translate", &translate_->x, 0.5f);
      ImGui::TreePop();
   }
}

Math::Vector::Vec3 CLEYERA::Util::TransformBase::GetWorldPos(){
   Math::Vector::Vec3 pos = Vec3(mat_.m[3][0], mat_.m[3][1], mat_.m[3][2]);
   return pos;
}

Math::Vector::Vec3 CLEYERA::Util::TransformBase::GetWorldRotate() {

   Vec3 scale = GetWorldScale();
   Math::Matrix::Mat4x4 rotationMatrix = mat_;

   rotationMatrix.m[0][0] /= scale.x;
   rotationMatrix.m[0][1] /= scale.x;
   rotationMatrix.m[0][2] /= scale.x;

   rotationMatrix.m[1][0] /= scale.y;
   rotationMatrix.m[1][1] /= scale.y;
   rotationMatrix.m[1][2] /= scale.y;

   rotationMatrix.m[2][0] /= scale.z;
   rotationMatrix.m[2][1] /= scale.z;
   rotationMatrix.m[2][2] /= scale.z;

   float pitch = asinf(-rotationMatrix.m[2][1]);
   float yaw = atan2f(rotationMatrix.m[2][0], rotationMatrix.m[2][2]);
   float roll = atan2f(rotationMatrix.m[0][1], rotationMatrix.m[1][1]);

   return Vec3(pitch, yaw, roll);
}

Math::Vector::Vec3 CLEYERA::Util::TransformBase::GetWorldScale() {

   return Vec3(sqrtf(mat_.m[0][0] * mat_.m[0][0] + mat_.m[0][1] * mat_.m[0][1] + mat_.m[0][2] * mat_.m[0][2]), sqrtf(mat_.m[1][0] * mat_.m[1][0] + mat_.m[1][1] * mat_.m[1][1] + mat_.m[1][2] * mat_.m[1][2]),
               sqrtf(mat_.m[2][0] * mat_.m[2][0] + mat_.m[2][1] * mat_.m[2][1] + mat_.m[2][2] * mat_.m[2][2]));
}

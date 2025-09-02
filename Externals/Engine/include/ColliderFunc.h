#pragma once
#include "SCollider.h"
#include "pch/Pch.h"

namespace CLEYERA {

namespace Util {

namespace Collider {

namespace system {

namespace Func {

std::array<Math::Vector::Vec3, 3> CreateOrientations(const Math::Vector::Vec3 &rotate);

void MakeLinesFromOBB(std::vector<Math::Vector::Vec3> &outLines, const OBB &obb);
void MakeLinesFromAABB(std::vector<Math::Vector::Vec3> &outLines, const Math::Vector::Vec3 &min,
                       const Math::Vector::Vec3 &max);

bool OBBCheck(const OBB &obb1, const OBB &obb2);
bool AABBCheck(const AABB &aabb1, const AABB &aabb2);

Math::Vector::Vec3 AABBComputePushOutVector(const AABB &aabb1, const AABB &aabb2);

// 射影の重複チェック
bool TestAxis(const Math::Vector::Vec3 &axis, const OBB &obb1, const OBB &obb2);
// 頂点を軸に射影
std::pair<float, float> OBBProjection(const OBB &obb, const Math::Vector::Vec3 &axis);

bool ProjectionOverlap(const std::pair<float, float> &projection1,
                       const std::pair<float, float> &projection2);

bool CalculateMTV(const Util::Collider::system::OBB &obbA, const Util::Collider::system::OBB &obbB,
                  Math::Vector::Vec3 &mtv, float &penetrationDepth);

void ProjectOntoAxis(const Math::Vector::Vec3 &axis, float &min, float &max,
                     const Util::Collider::system::OBB &obb);

std::vector<Math::Vector::Vec3> GetVertices(const Util::Collider::system::OBB &obb);

Math::Vector::Vec3 PushOutOBB(Util::Collider::system::OBB &obbA, Util::Collider::system::OBB &obbB);

Math::Vector::Vec3 PushOutAABB(Util::Collider::system::OBB &obbA,
                               Util::Collider::system::OBB &obbB);

} // namespace Func
} // namespace system
} // namespace Collider
} // namespace Util
} // namespace CLEYERA
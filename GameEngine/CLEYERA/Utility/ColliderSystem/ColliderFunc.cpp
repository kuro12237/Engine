#include "ColliderFunc.h"
#include <algorithm>

using namespace CLEYERA::Util::Collider::system::Func;
using namespace CLEYERA::Util::Collider::system;

std::array<Math::Vector::Vec3, 3> CreateOrientations(const Math::Vector::Vec3 &rotate) {
  float cx = std::cos(rotate.x);
  float sx = std::sin(rotate.x);
  float cy = std::cos(rotate.y);
  float sy = std::sin(rotate.y);
  float cz = std::cos(rotate.z);
  float sz = std::sin(rotate.z);

  // 回転行列 R = Rz * Ry * Rx の各軸を列ベクトルとして抽出
  Math::Vector::Vec3 right = {cy * cz, sx * sy * cz - cx * sz, cx * sy * cz + sx * sz};

  Math::Vector::Vec3 up = {cy * sz, sx * sy * sz + cx * cz, cx * sy * sz - sx * cz};

  Math::Vector::Vec3 forward = {-sy, sx * cy, cx * cy};

  return {right, up, forward};
}

void CLEYERA::Util::Collider::system::Func::MakeLinesFromOBB(
    std::vector<Math::Vector::Vec3> &outLines, const OBB &obb) {
  using Vec3 = Math::Vector::Vec3;

  // 軸方向 × ハーフサイズ
  Vec3 right = obb.orientations[0] * (obb.size.x * 0.5f);
  Vec3 up = obb.orientations[1] * (obb.size.y * 0.5f);
  Vec3 forward = obb.orientations[2] * (obb.size.z * 0.5f);

  // 8頂点を計算
  Vec3 corners[8];
  int i = 0;
  for (int dy : {-1, 1}) {
    for (int dz : {-1, 1}) {
      for (int dx : {-1, 1}) {

        Math::Vector::Vec3 vec = right * static_cast<float>(dx) + up * static_cast<float>(dy) +
                                 forward * static_cast<float>(dz);
        corners[i++] = *obb.center / 2 + vec;
      }
    }
  }

  // 辺（12本 × 2頂点）
  constexpr int edgeIndices[12][2] = {
      {0, 1}, {1, 3}, {3, 2}, {2, 0}, // 下面
      {4, 5}, {5, 7}, {7, 6}, {6, 4}, // 上面
      {0, 4}, {1, 5}, {2, 6}, {3, 7}  // 側面
  };

  outLines.clear();
  outLines.resize(48);
  int index = 0;
  for (auto &edge : edgeIndices) {
    outLines[index++] = (corners[edge[0]]);
    outLines[index++] = (corners[edge[1]]);
  }
}

void CLEYERA::Util::Collider::system::Func::MakeLinesFromAABB(
    std::vector<Math::Vector::Vec3> &outLines, const Math::Vector::Vec3 &min,
                       const Math::Vector::Vec3 &max) {
  using Vec3 = Math::Vector::Vec3;

  // 8 頂点（min/max から生成）
  Vec3 corners[8] = {
      {min.x, min.y, min.z}, {max.x, min.y, min.z}, {min.x, min.y, max.z}, {max.x, min.y, max.z},
      {min.x, max.y, min.z}, {max.x, max.y, min.z}, {min.x, max.y, max.z}, {max.x, max.y, max.z},
  };

  // エッジのインデックス（12本のライン）
  constexpr int edgeIndices[12][2] = {
      {0, 1}, {1, 3}, {3, 2}, {2, 0}, // 下の面
      {4, 5}, {5, 7}, {7, 6}, {6, 4}, // 上の面
      {0, 4}, {1, 5}, {2, 6}, {3, 7}  // 側面
  };

  outLines.clear();
  outLines.reserve(24); // 12本 × 2頂点

  for (const auto &edge : edgeIndices) {
    outLines.push_back(corners[edge[0]]);
    outLines.push_back(corners[edge[1]]);
  }
}

bool CLEYERA::Util::Collider::system::Func::OBBCheck(const OBB &obb1, const OBB &obb2) {

  // 分離軸テスト
  for (const auto &axis : obb1.orientations) {
    if (!TestAxis(axis, obb1, obb2)) {
      return false;
    }
  }

  for (const auto &axis : obb2.orientations) {
    if (!TestAxis(axis, obb1, obb2)) {
      return false;
    }
  }

  // OBB1の軸とOBB2の軸に垂直な軸をテスト
  for (const auto &axis :
       {Math::Vector::Vec3{obb1.orientations[1].x * obb2.orientations[2].x -
                               obb1.orientations[2].x * obb2.orientations[1].x,
                           obb1.orientations[1].y * obb2.orientations[2].y -
                               obb1.orientations[2].y * obb2.orientations[1].y,
                           obb1.orientations[1].z * obb2.orientations[2].z -
                               obb1.orientations[2].z * obb2.orientations[1].z},
        Math::Vector::Vec3{obb1.orientations[2].x * obb2.orientations[0].x -
                               obb1.orientations[0].x * obb2.orientations[2].x,
                           obb1.orientations[2].y * obb2.orientations[0].y -
                               obb1.orientations[0].y * obb2.orientations[2].y,
                           obb1.orientations[2].z * obb2.orientations[0].z -
                               obb1.orientations[0].z * obb2.orientations[2].z},
        Math::Vector::Vec3{obb1.orientations[0].x * obb2.orientations[1].x -
                               obb1.orientations[1].x * obb2.orientations[0].x,
                           obb1.orientations[0].y * obb2.orientations[1].y -
                               obb1.orientations[1].y * obb2.orientations[0].y,
                           obb1.orientations[0].z * obb2.orientations[1].z -
                               obb1.orientations[1].z * obb2.orientations[0].z}}) {
    if (!TestAxis(axis, obb1, obb2)) {
      return false;
    }
  }

  return true;
}

bool CLEYERA::Util::Collider::system::Func::AABBCheck(const AABB &aabb1, const AABB &aabb2) {
  Math::Vector::Vec3 aMin = aabb1.min + *aabb1.pos;
  Math::Vector::Vec3 aMax = aabb1.max + *aabb1.pos;
  Math::Vector::Vec3 bMin = aabb2.min + *aabb2.pos;
  Math::Vector::Vec3 bMax = aabb2.max + *aabb2.pos;

  return (aMin.x <= bMax.x && aMax.x >= bMin.x) && (aMin.y <= bMax.y && aMax.y >= bMin.y) &&
         (aMin.z <= bMax.z && aMax.z >= bMin.z);
}

Math::Vector::Vec3
CLEYERA::Util::Collider::system::Func::AABBComputePushOutVector(const AABB &aabb1,
                                                                const AABB &aabb2) {
  auto aCenter = aabb1.GetWorldCenter();
  auto bCenter = aabb2.GetWorldCenter();
  auto aHalf = aabb1.HalfSize();
  auto bHalf = aabb2.HalfSize();

  float dx = bCenter.x - aCenter.x;
  float dy = bCenter.y - aCenter.y;
  float dz = bCenter.z - aCenter.z;

  float px = (aHalf.x + bHalf.x) - std::abs(dx);
  float py = (aHalf.y + bHalf.y) - std::abs(dy);
  float pz = (aHalf.z + bHalf.z) - std::abs(dz);

  Math::Vector::Vec3 push(0, 0, 0);
  if (px < py && px < pz) {
    push.x = (dx < 0) ? -px : px;
  } else if (py < px && py < pz) {
    push.y = (dy < 0) ? -py : py;
  } else {
    push.z = (dz < 0) ? -pz : pz;
  }

  return push;
}

bool CLEYERA::Util::Collider::system::Func::TestAxis(const Math::Vector::Vec3 &axis,
                                                     const OBB &obb1, const OBB &obb2) {

  // OBBの射影を計算
  auto projection1 = OBBProjection(obb1, axis);
  auto projection2 = OBBProjection(obb2, axis);

  // 射影が重なっているかチェック
  return ProjectionOverlap(projection1, projection2);
}

std::pair<float, float>
CLEYERA::Util::Collider::system::Func::OBBProjection(const OBB &obb,
                                                     const Math::Vector::Vec3 &axis) {

  float val = std::sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z); // 正規化
  float newAxis = 0.0f;
  newAxis = newAxis / val;

  // OBB上の頂点を取得
  std::array<Math::Vector::Vec3, 8> vertices{};
  for (int i = 0; i < 8; ++i) {
    Math::Vector::Vec3 sign = {(i & 1) ? 1.0f : -1.0f, (i & 2) ? 1.0f : -1.0f,
                               (i & 4) ? 1.0f : -1.0f};
    vertices[i] = {obb.center->x + obb.orientations[0].x * sign.x * (obb.size.x / 2) +
                       obb.orientations[1].x * sign.y * (obb.size.y / 2) +
                       obb.orientations[2].x * sign.z * (obb.size.z / 2),
                   obb.center->y + obb.orientations[0].y * sign.x * (obb.size.x / 2) +
                       obb.orientations[1].y * sign.y * (obb.size.y / 2) +
                       obb.orientations[2].y * sign.z * (obb.size.z / 2),
                   obb.center->z + obb.orientations[0].z * sign.x * (obb.size.x / 2) +
                       obb.orientations[1].z * sign.y * (obb.size.y / 2) +
                       obb.orientations[2].z * sign.z * (obb.size.z / 2)};
  }

  // 頂点を軸に射影
  std::array<float, 8> projections{};
  for (int i = 0; i < 8; ++i) {
    projections[i] = vertices[i].x * axis.x + vertices[i].y * axis.y + vertices[i].z * axis.z;
  }

  auto minmax = std::minmax_element(projections.begin(), projections.end());
  return std::make_pair(*minmax.first, *minmax.second);
}

bool CLEYERA::Util::Collider::system::Func::ProjectionOverlap(
    const std::pair<float, float> &projection1, const std::pair<float, float> &projection2) {

  // 射影の重なりをチェック
  return (projection1.first <= projection2.second && projection2.first <= projection1.second);
}

bool CLEYERA::Util::Collider::system::Func::CalculateMTV(const Util::Collider::system::OBB &obbA,
                                                         const Util::Collider::system::OBB &obbB,
                                                         Math::Vector::Vec3 &mtv,
                                                         float &penetrationDepth) // OBB の軸を取得
{
  std::vector<Math::Vector::Vec3> axes = {obbA.orientations[0], obbA.orientations[1],
                                          obbA.orientations[2]};

  const auto &axesB = {obbB.orientations[0], obbB.orientations[1], obbB.orientations[2]};

  axes.insert(axes.end(), axesB.begin(), axesB.end());

  // 最小分離ベクトルを初期化
  penetrationDepth = std::numeric_limits<float>::max();

  for (const auto &axis : axes) {
    // 軸を正規化
    Math::Vector::Vec3 normalizedAxis = Math::Vector::Func::Normalize(axis);

    // OBB A と OBB B の投影範囲を計算
    float minA, maxA, minB, maxB;
    ProjectOntoAxis(normalizedAxis, minA, maxA, obbA);
    ProjectOntoAxis(normalizedAxis, minB, maxB, obbB);

    // 投影範囲が重なっているかを確認
    float overlap = std::min(maxA, maxB) - std::max(minA, minB);
    if (overlap <= 0) {
      // 重なりがない場合、衝突していない
      return false;
    }

    // 最小の重なりを記録
    if (overlap < penetrationDepth) {
      penetrationDepth = overlap;
      mtv = normalizedAxis;
    }
  }

  return true;
}

void CLEYERA::Util::Collider::system::Func::ProjectOntoAxis(
    const Math::Vector::Vec3 &axis, float &min, float &max,
    const Util::Collider::system::OBB &obb) {

  // OBB の頂点を取得
  std::vector<Math::Vector::Vec3> vertices = GetVertices(obb);

  // 各頂点を軸に投影
  min = max = Math::Vector::Func::Dot(vertices[0], axis);
  for (const auto &vertex : vertices) {
    float projection = Math::Vector::Func::Dot(vertex, axis);
    if (projection < min)
      min = projection;
    if (projection > max)
      max = projection;
  }
}

std::vector<Math::Vector::Vec3>
CLEYERA::Util::Collider::system::Func::GetVertices(const Util::Collider::system::OBB &obb) {
  std::vector<Math::Vector::Vec3> vertices;

  // 軸方向 × ハーフサイズ
  Math::Vector::Vec3 right = obb.orientations[0] * (obb.size.x);
  Math::Vector::Vec3 up = obb.orientations[1] * (obb.size.y);
  Math::Vector::Vec3 forward = obb.orientations[2] * (obb.size.z);

  // 8 頂点を計算
  int index = 0;
  vertices.resize(24);
  for (int dx : {-1, 1}) {
    for (int dy : {-1, 1}) {
      for (int dz : {-1, 1}) {
        vertices[index++] = *obb.center + right * static_cast<float>(dx) +
                            up * static_cast<float>(dy) + forward * static_cast<float>(dz);
      }
    }
  }

  return vertices;
}

Math::Vector::Vec3
CLEYERA::Util::Collider::system::Func::PushOutOBB(Util::Collider::system::OBB &obbA,
                                                  Util::Collider::system::OBB &obbB) {
  Math::Vector::Vec3 mtv;
  float penetrationDepth;

  if (Util::Collider::system::Func::CalculateMTV(obbA, obbB, mtv, penetrationDepth)) {
    // MTV の方向を確認し、必要であれば反転
    if (Math::Vector::Func::Dot(mtv, *obbB.center - *obbA.center) < 0) {
      mtv = mtv * -1;
    }

    // 押し出しベクトルを計算
    Math::Vector::Vec3 pushVector = mtv * penetrationDepth;

    // 押し出しベクトルが小さすぎる場合は無視
    if (Math::Vector::Func::Length(pushVector) < 1e-4f) {
      return {};
    }

    return pushVector;
  }

  return {};
}

Math::Vector::Vec3
CLEYERA::Util::Collider::system::Func::PushOutAABB(Util::Collider::system::OBB &obbA,
                                                   Util::Collider::system::OBB &obbB) {
  Math::Vector::Vec3 overlap;
  Math::Vector::Vec3 halfSizeA = obbA.size * 0.5f;
  Math::Vector::Vec3 minA = *obbA.center - halfSizeA;
  Math::Vector::Vec3 maxA = *obbA.center + halfSizeA;

  Math::Vector::Vec3 halfSizeB = obbB.size * 0.5f;
  Math::Vector::Vec3 minB = *obbB.center - halfSizeB;
  Math::Vector::Vec3 maxB = *obbB.center + halfSizeB;

  using Vector3 = Math::Vector::Vec3;

  if (maxA.x > minB.x && minA.x < maxB.x) {
    float overlapX = std::min(maxA.x - minB.x, maxA.x - minB.x);
    overlap.x = overlapX;
  }
  if (maxA.y > minB.y && minA.y < maxB.y) {
    float overlapY = std::min(maxA.y - minB.y, maxA.y - minB.y);
    overlap.y = overlapY;
  }
  if (maxA.z > minB.z && minA.z < maxB.z) {
    float overlapZ = std::min(maxA.z - minB.z, maxA.z - minB.z);
    overlap.z = overlapZ;
  }

  if (overlap.x <= 0.0f || overlap.y <= 0.0f || overlap.z <= 0.0f) {
    return Vector3(); // オーバーラップなし
  }

  Vector3 push = Vector3(0.0f, 0.0f, 0.0f);

  // x
  if (overlap.x <= overlap.y && overlap.x <= overlap.z) {

    if (obbA.center->x < obbB.center->x) {
      push.x = -overlap.x;
    } else {
      push.x = overlap.x;
    }
  } else if (overlap.y <= overlap.x && overlap.y <= overlap.z) {
    // y
    if (obbA.center->y < obbB.center->y) {
      push.y = -overlap.y;
    } else {
      push.y = overlap.y;
    }
  } else { // z
    if (obbA.center->z < obbB.center->z) {
      push.z = -overlap.z;
    } else {
      push.z = overlap.z;
    }
  }

  return push;
}

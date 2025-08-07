#include "Octree.h"
#include <iostream>

using Vector3 = Math::Vector::Vec3;

void CLEYERA::Util::Collider::Octree::Init() {

  divisionLevel = 4;
  spaceSize = 1000.0f;
  centerPosition = {0.0f, 0.0f, 0.0f};
}

bool CLEYERA::Util::Collider::Octree::IsInside(
    const Math::Vector::Vec3 &p) const {
  const Vector3 min = GetMin();
  const Vector3 max = GetMax();
  return (p.x >= min.x && p.x <= max.x) && (p.y >= min.y && p.y <= max.y) &&
         (p.z >= min.z && p.z <= max.z);
}

int CLEYERA::Util::Collider::Octree::GetMortonNumber(
    Math::Vector::Vec3 position) {

  if (!IsInside(position))
    return -1;

  Vector3 local = (position - GetMin()) / GetCellSize();
  int mortonIndex = GetMortonOrder(local);
  return mortonIndex + GetLinearIndexOffset(divisionLevel);
}

int CLEYERA::Util::Collider::Octree::GetMortonNumber(Math::Vector::Vec3 min,
                                                     Math::Vector::Vec3 max) {
  Vector3 localMin = (min - GetMin()) / GetCellSize();
  Vector3 localMax = (max - GetMin()) / GetCellSize();

  int mortonMin = GetMortonOrder(localMin);
  int mortonMax = GetMortonOrder(localMax);

  int xorVal = mortonMin ^ mortonMax;
  int level = divisionLevel - 1;

  while (xorVal > 0) {
    xorVal >>= 3;
    --level;
  }
  int mortonIndex = mortonMax >> ((divisionLevel - level) * 3);
  return mortonIndex + GetLinearIndexOffset(level);
}

DWORD CLEYERA::Util::Collider::Octree::GetMortonOrder(
    const Math::Vector::Vec3 &point) {

  //
  return BitSeparate(static_cast<BYTE>(point.x)) |
         (BitSeparate(static_cast<BYTE>(point.y)) << 1) |
         (BitSeparate(static_cast<BYTE>(point.z)) << 2);
}

DWORD CLEYERA::Util::Collider::Octree::BitSeparate(BYTE n) {
  n = (n | (n << 8)) & 0x0F00F;
  n = (n | (n << 4)) & 0x0C30C3;
  n = (n | (n << 2)) & 0x249249;
  return n;
}

int CLEYERA::Util::Collider::Octree::GetCellCountAtLevel(int level) const {
  //
  return int(powf(8.0f, float(level)));
}

int CLEYERA::Util::Collider::Octree::GetLinearIndexOffset(int level) const {
  if (level <= 0)
    return 0;
  return (GetCellCountAtLevel(level) - 1) / 7;
}

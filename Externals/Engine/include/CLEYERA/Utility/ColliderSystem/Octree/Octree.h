#pragma once
#include "pch/Pch.h"

namespace CLEYERA {

namespace Util {

namespace Collider {

class Octree {
 public:
   Octree() {};
   ~Octree() {};

   // 初期化
   void Init();

   // 指定座標がオクツリー空間内にあるか
   bool IsInside(const Math::Vector::Vec3 &p) const;

   // 1点からモートン番号を取得
   int GetMortonNumber(Math::Vector::Vec3 position);

   // AABBからモートン番号を取得
   int GetMortonNumber(Math::Vector::Vec3 min, Math::Vector::Vec3 max);


 private:
   // モートンオーダー取得
   DWORD GetMortonOrder(const Math::Vector::Vec3 &point);

   // ビット分離（1軸用）
   DWORD BitSeparate(BYTE n);

   // 指定レベルでのセル数（8^n）
   int GetCellCountAtLevel(int level) const;

   // 線形オフセットを取得（レベルごとの空間数合計）
   int GetLinearIndexOffset(int level) const;

   // 空間サイズの1辺（全体空間は cube ）
   float spaceSize = 1000.0f;

   // 空間の中心位置
   Math::Vector::Vec3 centerPosition;

   // 分割レベル（0以上）
   uint32_t divisionLevel = 4;

   // 空間の最小座標
   Math::Vector::Vec3 GetMin() const { return centerPosition - Math::Vector::Vec3(spaceSize * 0.5f, spaceSize * 0.5f, spaceSize * 0.5f); }

   // 空間の最大座標
   Math::Vector::Vec3 GetMax() const { return centerPosition + Math::Vector::Vec3(spaceSize * 0.5f, spaceSize * 0.5f, spaceSize * 0.5f); }

   // 1セルあたりのサイズ
   float GetCellSize() const { return spaceSize / static_cast<float>(1 << divisionLevel); }
};

} // namespace Collider
} // namespace Util
} // namespace CLEYERA
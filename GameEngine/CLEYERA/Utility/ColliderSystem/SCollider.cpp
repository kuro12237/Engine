#include "SCollider.h"

bool CLEYERA::Util::Collider::system::Triangle::contains(const Math::Vector::Vec3 &p) {

   using Vec3 = Math::Vector::Vec3;

   // この三角形を「真上」から見た時、点(p.x p.z)が含まれているか？
   bool flag = true;
   for (int i = 0; flag == true && i < 3; i++) {
      Vec3 pv = p - vertex[i];
      // 辺ベクトルとｐベクトルの「外積ｙ成分」
      float y = edgeVec[i].z * pv.x - edgeVec[i].x * pv.z;
      if (y < 0) {
         // 含まれていない
         flag = false;
      }
   }

   return flag;
}

float CLEYERA::Util::Collider::system::Triangle::getY(const Math::Vector::Vec3 &p) { return (-normal.x * p.x - normal.z * p.z - dot) / normal.y; }

#pragma once
#include "../DX/DXBufferResource/DXBufferResource.h"
#include "../DX/DXManager.h"
#include "math.h"


namespace CLEYERA {

namespace Sprite2d {

namespace System {

struct Mesh2d{

  Math::Vector::Vec4 vertex = {};
  Math::Vector::Vec2 texCoord = {};
};

class SpriteMesh {
public:
  SpriteMesh();
  ~SpriteMesh() {};

  void Create();

  void Transfar();

  void CommandIBVB();

  void SetMeshData(const std::vector<Mesh2d> &m) { mesh_ = &m; }



private:
  std::unique_ptr<Base::DX::DXBufferResource<Mesh2d>> vertexBuf_ = nullptr;
  const std::vector<Mesh2d> *mesh_;

  std::unique_ptr<Base::DX::DXBufferResource<int32_t>> indexBuf_ = nullptr;
  std::vector<int32_t> index_;
};

} // namespace System

} // namespace Sprite2d

} // namespace CLEYERA

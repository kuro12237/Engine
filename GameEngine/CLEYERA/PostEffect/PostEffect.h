#pragma once
#include "../DX/DXManager.h"
#include "3d/Mesh/MeshData.h"
#include "Utility/World/WorldTransform.h"
#include "pch/Pch.h"

namespace CLEYERA {

namespace Manager {

/// <summary>
/// ポストエフェクト管理クラス
/// </summary>
class PostEffectManager {
public:
  static PostEffectManager *GetInstance() {
    static PostEffectManager ins;
    return &ins;
  }

  void Init();
  void Update();
  void FInalize();


  void Draw();

  /// <summary>
  /// 前処理
  /// </summary>
  void PreDraw();

  /// <summary>
  /// 後処理
  /// </summary>
  void PostDraw();

private:
  std::unique_ptr<Base::DX::DXBufferResource<Model3d::system::VertexForGPU>> vert_;
  std::vector<Model3d::system::VertexForGPU> vertData_;

  std::unique_ptr<Util::WorldTransform> worldTransform_ = nullptr;
  Math::Vector::Vec3 scale_ = {1.0f,1.0f,1.0f};
  Math::Vector::Vec3 rotate_ = {};
  Math::Vector::Vec3 translate_ = {};

  Math::Vector::Vec2 size_ = {1280.0f, 720.0f};

  std::unique_ptr<Base::DX::DXBufferResource<uint32_t>> albedo_;
  std::unique_ptr<Base::DX::DXBufferResource<uint32_t>> depth_;

};

} // namespace Manager

} // namespace CLEYERA

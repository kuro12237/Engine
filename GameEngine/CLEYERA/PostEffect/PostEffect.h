#pragma once
#include "../DX/DXManager.h"
#include "3d/Mesh/MeshData.h"
#include "Utility/World/WorldTransform.h"
#include "pch/Pch.h"

namespace CLEYERA {

namespace Manager {

namespace System {

enum class PostEffectBuf { Vert, World, Albedo,Normal ,Depth};
}

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

  void CommandCall(const System::PostEffectBuf &mode, uint32_t num = 0);

  const std::vector<Model3d::system::VertexForGPU> &GetVertData() const {
    return vertData_;
  }

private:
  std::unique_ptr<CLEYERA::Base::DX::DXBufferResource<uint32_t>> CreateTexture();

  std::unique_ptr<Base::DX::DXBufferResource<Model3d::system::VertexForGPU>>
      vert_;
  std::vector<Model3d::system::VertexForGPU> vertData_;

  Math::Vector::Vec3 scale_ = {1.0f, 1.0f, 1.0f};
  Math::Vector::Vec3 rotate_ = {};
  Math::Vector::Vec3 translate_ = {};

  Math::Vector::Vec2 size_ = {1280.0f, 720.0f};

  std::unique_ptr<Util::WorldTransform> worldTransform_ = nullptr;
  std::unique_ptr<Base::DX::DXBufferResource<uint32_t>> albedo_ = nullptr;
  std::unique_ptr<Base::DX::DXBufferResource<uint32_t>> normal_ = nullptr;
  std::unique_ptr<Base::DX::DXBufferResource<uint32_t>> depth_ = nullptr;

  std::unique_ptr<Base::DX::DXBufferResource<uint32_t>> shadow_ = nullptr;
};

} // namespace Manager

} // namespace CLEYERA

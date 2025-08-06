#pragma once
#include "RasterPiplineCommon.h"

namespace CLEYERA {

namespace Graphics {

namespace Raster {

/// <summary>
/// ラスタ描画のパイプライン管理クラス
/// </summary>
class RasterPiplineManager {
public:
  static RasterPiplineManager *GetInstance();

  void Init();

  void SetRootsignature(Graphics::RasterPipline_Mode3d mode);
  void SetPipline(Graphics::RasterPipline_Mode3d mode);

  void SetRootsignature(Graphics::RasterPipline_Mode2d mode);
  void SetPipline(Graphics::RasterPipline_Mode2d mode);


  void SetPostEffectRootsignature(Graphics::PostEffect_Mode mode);
  void SetPostEffectPipline(Graphics::PostEffect_Mode mode);

#pragma region Set
  void SetCommon(std::weak_ptr<Raster::system::RasterPiplineCommon> c) { common_ = c; };
#pragma endregion

  template <typename T> std::weak_ptr<T> GetPipline(Graphics::RasterPipline_Mode3d mode) {
    return common_.lock()->Getpipline<T>(mode);
  }

private:
  std::weak_ptr<Raster::system::RasterPiplineCommon> common_;

  Base::DX::DXCommandManager *commandManager_ = nullptr;

#pragma region Single

  RasterPiplineManager() = default;
  ~RasterPiplineManager() = default;
  RasterPiplineManager(const RasterPiplineManager &) = delete;
  RasterPiplineManager &operator=(const RasterPiplineManager &) = delete;

#pragma endregion
};

} // namespace Raster
} // namespace Graphics
} // namespace CLEYERA
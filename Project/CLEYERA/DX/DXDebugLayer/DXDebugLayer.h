#pragma once
#include "../DXComponent.h"

namespace CLEYERA {
namespace Base {
namespace DX {

using Microsoft::WRL::ComPtr;

/// <summary>
///
/// </summary>
class DXDebugLayer : public DXComponent {
public:
  DXDebugLayer(const std::string &name) : DXComponent(name) {};
  ~DXDebugLayer() = default;

  void Create() override;

#pragma region Get

#pragma endregion

private:
  ComPtr<ID3D12Debug1> debugController = nullptr;
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA
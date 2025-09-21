#pragma once

#include "../DXComponent.h"

namespace CLEYERA {
namespace Base {
namespace DX {

using Microsoft::WRL::ComPtr;

/// <summary>
/// DirectXDevice
/// </summary>
class DXDevice : public DXComponent {
public:
  DXDevice(const std::string &name) : DXComponent(name) {};
  ~DXDevice() = default;

  void Create() override;

#pragma region Get

  ID3D12Device5 *GetDevice() { return device_.Get(); }

#pragma endregion

private:
  ComPtr<ID3D12Device5> device_ = nullptr;
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA
#pragma once
#include "../DXComponent.h"

namespace CLEYERA {
namespace Base {
namespace DX {
using Microsoft::WRL::ComPtr;

/// <summary>
///
/// </summary>
class DXInfoQueue : public DXComponent {
public:
  DXInfoQueue(const std::string &name) : DXComponent(name) {};
  ~DXInfoQueue() = default;

  void Create() override;

#pragma region Get

  ID3D12InfoQueue *GetinfoQueue() { return infoQueue_.Get(); }
#pragma endregion

private:
  ComPtr<ID3D12InfoQueue> infoQueue_ = nullptr;
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA
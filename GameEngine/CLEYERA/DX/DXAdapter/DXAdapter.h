#pragma once
#include "../../SystemLogManager/ConvertString.h"
#include "../DXComponent.h"

namespace CLEYERA {
namespace Base {
namespace DX {

using Microsoft::WRL::ComPtr;

/// <summary>
/// DXAdapetrクラス
/// </summary>
class DXAdapter : public DXComponent {
public:
  DXAdapter(const std::string &name) : DXComponent(name) {};
  ~DXAdapter() = default;

  void Create() override;

#pragma region Get

  IDXGIAdapter4 *GetAdapter() { return adapter_.Get(); }
#pragma endregion

private:
  ComPtr<IDXGIAdapter4> adapter_ = nullptr;
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA
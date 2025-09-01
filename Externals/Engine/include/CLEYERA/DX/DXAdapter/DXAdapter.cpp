#include "DXAdapter.h"
#include "../DXManager.h"

using namespace CLEYERA::Base::DX;

void DXAdapter::Create() {
  dxManager_ = DXManager::GetInstance();

  IDXGIFactory7 *factory = dxManager_->GetFactory();

  for (UINT i = 0; factory->EnumAdapterByGpuPreference(
                       i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
                       IID_PPV_ARGS(&adapter_)) != DXGI_ERROR_NOT_FOUND;
       i++) {
    DXGI_ADAPTER_DESC3 adapterDesc{};
    [[maybe_unused]] HRESULT hr = adapter_->GetDesc3(&adapterDesc);
    assert(SUCCEEDED(hr));

    if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
      std::string msg =ConvertString(std::format(L"Use Adapater:{}\n", adapterDesc.Description));
      NotifyObservesMsg(msg);

      break;
    }
    adapter_ = nullptr;
  }
  assert(adapter_ != nullptr);

  NotifyObserversCreateComp();
}
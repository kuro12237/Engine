#include "DXDevice.h"
#include "../DXManager.h"

using namespace CLEYERA::Base::DX;

void DXDevice::Create() {

  dxManager_ = DXManager::GetInstance();

  D3D_FEATURE_LEVEL featureLevels[] = {
      D3D_FEATURE_LEVEL_12_2, D3D_FEATURE_LEVEL_12_1, D3D_FEATURE_LEVEL_12_0};

  const char *featureLevelStrings[] = {"12.2", "12.1", "12.0"};

  IDXGIAdapter4 *adapter = dxManager_->GetAdapter();

  for (size_t i = 0; i < _countof(featureLevels); i++) {
    HRESULT hr =
        D3D12CreateDevice(adapter, featureLevels[i], IID_PPV_ARGS(&device_));
    if (SUCCEEDED(hr)) {
      NotifyObservesMsg(
          std::format("FeatureLevel : {}\n", featureLevelStrings[i]));
      break;
    }
  }

  NotifyObserversCreateComp();

  D3D12_FEATURE_DATA_D3D12_OPTIONS5 options{};
  HRESULT hr = device_->CheckFeatureSupport(
      D3D12_FEATURE_D3D12_OPTIONS5, &options, sizeof(options));

  if (FAILED(hr) ||
      options.RaytracingTier == D3D12_RAYTRACING_TIER_NOT_SUPPORTED) {
    throw std::runtime_error("DirectX Raytracing not support");
  }
}
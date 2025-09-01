#include "DXFactory.h"
#include "../DXManager.h"
using namespace CLEYERA::Base::DX;

void DXFactory::Create() {

  dxManager_ = DXManager::GetInstance();
  [[maybe_unused]]HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&factory_));
  assert(SUCCEEDED(hr));
  NotifyObserversCreateComp();
}
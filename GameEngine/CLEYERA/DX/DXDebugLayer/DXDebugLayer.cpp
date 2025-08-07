#include "DXDebugLayer.h"

void CLEYERA::Base::DX::DXDebugLayer::Create() {

  if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
    debugController->EnableDebugLayer();
    debugController->SetEnableGPUBasedValidation(TRUE);
  }

  NotifyObserversCreateComp();
}
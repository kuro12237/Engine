#pragma once
#include "DXComponent.h"

#include "../SystemLogManager/SystemLogManager.h"
#include "DXAdapter/DXAdapter.h"
#include "DXCommand/DXCommandAllocator.h"
#include "DXCommand/DXCommandList.h"
#include "DXCommand/DXCommandQueue.h"
#include "DXDebugLayer/DXDebugLayer.h"
#include "DXDevice/DXDevice.h"
#include "DXFactory/DXFactory.h"
#include "DXInfoQueue/DXInfoQueue.h"
#include "DXSwapChain/DXSwapChain.h"

#include "DXDescripter/DXDSVDescripter.h"
#include "DXDescripter/DXRTVDescripter.h"
#include "DXDescripter/DXSRVDescripter.h"
#include "DXFence/DXFence.h"
#include"DXDepth/DXDepth.h"

#include "DXBarrier/DXBarrier.h"

#include"DXDescripter/DXDescripterManager.h"

namespace CLEYERA {
namespace Base {
namespace DX {

enum class DXCommonBarrierTable { SwapChainBarrier = 0, Max = 1 };

/// <summary>
/// DXの本体を持つクラス
/// </summary>
class DXCommon : public DXComponent {
public:
  DXCommon(const std::string &name) : DXComponent(name) {};
  ~DXCommon() {};

  void Create() override;

  void Finalize();

  void PreDraw();

  void PostDraw();

  void ImGuiUpdate();

  void CommandReset();

#pragma region Get

  std::shared_ptr<DXFactory> GetFactory() { return factory_; }
  std::shared_ptr<DXAdapter> GetAdapter() { return adapter_; }
  std::shared_ptr<DXDevice> GetDevice() { return device_; }

#pragma endregion

#pragma region Set

  void SetLogManager(const std::shared_ptr<LogManager::SystemLogManager> &l) {
    logManager_ = l;
  }
#pragma endregion

private:
  UINT backBufferIndex_ = 0;

  std::weak_ptr<LogManager::SystemLogManager> logManager_;

  std::list<std::weak_ptr<DXComponent>> componentList_;

  std::shared_ptr<DXFence> fence_ = nullptr;
  std::shared_ptr<DXDSVDescripter> dsvDescripter_ = nullptr;
  std::shared_ptr<DXSRVDescripter> srvDescripter_ = nullptr;
  std::shared_ptr<DXRTVDescripter> rtvDescripter_ = nullptr;
  std::shared_ptr<DXSwapChain> swapChain_ = nullptr;

  std::shared_ptr<DXCommandList> commandList_ = nullptr;
  std::shared_ptr<DXCommandAllocator> commandAllcator_ = nullptr;
  std::shared_ptr<DXCommandQueue> commandQueue_ = nullptr;
  std::shared_ptr<DXFactory> factory_ = nullptr;
  std::shared_ptr<DXAdapter> adapter_ = nullptr;
  std::shared_ptr<DXDevice> device_ = nullptr;


  std::vector<std::unique_ptr<DXBarrier>> barriers_;

  std::shared_ptr<DXDepth>depth_=nullptr;

  
   D3D12_RENDER_TARGET_VIEW_DESC desc;
#ifdef _DEBUG

  std::shared_ptr<DXInfoQueue> infoQueue_ = nullptr;
  std::shared_ptr<DXDebugLayer> debugLayer_ = nullptr;
#endif // _DEBUG
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA
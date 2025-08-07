#pragma once
#include "../pch/Pch.h"
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

namespace CLEYERA {
namespace Base {
namespace DX {

class DXCommon;

/// <summary>
///
/// </summary>
class DXManager {
public:
  static DXManager *GetInstance() {
    static DXManager instance;
    return &instance;
  }

  void ImGuiUpdate();

#pragma region Set
  void SetDebugLayer(const std::weak_ptr<DXDebugLayer> &layer) {
    debugLayer_ = layer;
  }
  void SetAdapter(const std::weak_ptr<DXAdapter> &adapter) {
    adapter_ = adapter;
  }
  void SetFactory(const std::weak_ptr<DXFactory> &factory) {
    factory_ = factory;
  }
  void SetDevice(const std::weak_ptr<DXDevice> &device) { device_ = device; }

  void SetInfoQueue(const std::weak_ptr<DXInfoQueue> &queue) {
    infoQueue_ = queue;
  }
  void SetCommandQueue(const std::weak_ptr<DXCommandQueue> &queue) {
    commandQueue_ = queue;
  }
  void SetCommandAllocator(const std::weak_ptr<DXCommandAllocator> &allocator) {
    commandAllocator_ = allocator;
  }
  void SetCommandList(const std::weak_ptr<DXCommandList> &list) {
    commandList_ = list;
  }
  void SetSwapChain(const std::weak_ptr<DXSwapChain> &swapChain) {
    swapChain_ = swapChain;
  }
  void SetRTVDescripter(const std::weak_ptr<DXRTVDescripter> &descripter) {
    rtvDescripter_ = descripter;
  }
  void SetDepth(const std::weak_ptr<DXDepth> &depth) { depth_ = depth; }
#pragma endregion

#pragma region Get

  ID3D12Device5 *GetDevice() { return device_.lock()->GetDevice(); }
  IDXGIFactory7 *GetFactory() { return factory_.lock()->GetFactory(); }
  IDXGIAdapter4 *GetAdapter() { return adapter_.lock()->GetAdapter(); }

  ID3D12InfoQueue *GetInfoQueue() { return infoQueue_.lock()->GetinfoQueue(); }

  DXDepth *GetDepth() { return depth_.lock().get(); }

  ID3D12GraphicsCommandList4 *GetCommandList() {
    return commandList_.lock()->GetCommandList();
  }
  ID3D12CommandQueue *GetCommandQueue() {
    return commandQueue_.lock()->GetCommandQueue();
  }
  ID3D12CommandAllocator *GetCommandAllocator() {
    return commandAllocator_.lock()->GetCommandAllocator();
  }

  std::weak_ptr<DXSwapChain> GetSwapChain() { return swapChain_.lock(); }
#pragma endregion

private:
  std::weak_ptr<DXDebugLayer> debugLayer_;
  std::weak_ptr<DXAdapter> adapter_;
  std::weak_ptr<DXFactory> factory_;
  std::weak_ptr<DXDevice> device_;
  std::weak_ptr<DXInfoQueue> infoQueue_;
  std::weak_ptr<DXCommandQueue> commandQueue_;
  std::weak_ptr<DXCommandAllocator> commandAllocator_;
  std::weak_ptr<DXCommandList> commandList_;
  std::weak_ptr<DXSwapChain> swapChain_;
  
  std::weak_ptr<DXRTVDescripter> rtvDescripter_;
  std::weak_ptr<DXDSVDescripter> dsvDescripter_;
  std::weak_ptr<DXSRVDescripter> srvDescripter_;
  std::weak_ptr<DXDepth> depth_;

#pragma region Single

  DXManager() = default;
  ~DXManager() = default;
  DXManager(const DXManager &) = delete;
  DXManager &operator=(const DXManager &) = delete;

#pragma endregion
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA
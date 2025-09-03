#pragma once
#include "../DXCommand/DXCommandList.h"
#include "../DXComponent.h"
#include "../DXSwapChain/DXSwapChain.h"
#include "DXDescripterComponent.h"

namespace CLEYERA {
namespace Base {
namespace DX {

using Microsoft::WRL::ComPtr;

class DXDescripterComponent : public DXComponent {
public:
  DXDescripterComponent(const std::string &name) : DXComponent(name) {}
  virtual ~DXDescripterComponent() {};

  virtual void Create() = 0;
  
  void CreateDescripter(const D3D12_DESCRIPTOR_HEAP_TYPE &type,
                        bool shaderVisible);

  #pragma region Get

  ID3D12DescriptorHeap *GetDescripter() { return descripter_.Get(); }
  D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(size_t index) { return cpuHandles_[index]; }

  D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle(size_t index) { return gpuHandles_[index]; }
#pragma endregion



protected:

  ID3D12GraphicsCommandList *commandList_ = nullptr;

  ComPtr<ID3D12DescriptorHeap> descripter_ = nullptr;

  int32_t descripterSize_ = 1024;

  D3D12_DESCRIPTOR_HEAP_TYPE type_;
  size_t handleIndex_ = 0;
  //0は使わない

  std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> cpuHandles_;
  std::vector<D3D12_GPU_DESCRIPTOR_HANDLE> gpuHandles_;

  std::list<size_t> indexFreeList_;

private:
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA
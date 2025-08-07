#pragma once
#include "../../pch/Pch.h"

namespace CLEYERA {
namespace Base {
namespace DX {

class DXCommandManager {
 public:
   static DXCommandManager *GetInstace();

   void Init();

   void OMRenderTargets(const std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> &rtvHandles, const D3D12_CPU_DESCRIPTOR_HANDLE *dsvHandle);
   void ClearRenderTargetView(D3D12_CPU_DESCRIPTOR_HANDLE handle, const std::vector<float> &clearColor);
   void ClearDepthStencilView(D3D12_CPU_DESCRIPTOR_HANDLE handle, D3D12_CLEAR_FLAGS flag);

   void SetViewCommand(int32_t kWidth, int32_t height);
   void SetScissorCommand(int32_t kWidth, int32_t height);

   void SetDescripterHeap(const std::vector<ID3D12DescriptorHeap *> desc);

   void CommandClose();
   void CommandExecute();

   void WaitForIdleGpu();

   void SetDescripter(std::vector<ID3D12DescriptorHeap *> desc);

   void Barrier(const D3D12_RESOURCE_BARRIER &barrier);

   void ComputeRootSignature(ID3D12RootSignature *root);
   void ComputeDescripterTable(UINT num, D3D12_GPU_DESCRIPTOR_HANDLE handle);
   void GraphicsDescripterTable(UINT num, D3D12_GPU_DESCRIPTOR_HANDLE handle);

   void GraphicsCommandCall(UINT number, ID3D12Resource *buf);

   void GraphicsRootSignature(ID3D12RootSignature *root);
   void GraphicsPipelineState(ID3D12PipelineState *state);

   void VBCommandCall(const std::vector<D3D12_VERTEX_BUFFER_VIEW> &view);
   void IBCommandCall(const std::vector<D3D12_INDEX_BUFFER_VIEW>& view);

   void SetTopology(D3D_PRIMITIVE_TOPOLOGY type= D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
   void DrawIndexCall(UINT num);
   void DrawCall(UINT vertNum, UINT instanceid);

   void DispachRay(const D3D12_DISPATCH_RAYS_DESC &desc);


   /// <summary>
   /// targetにコピー
   /// </summary>
   /// <param name="target"></param>
   /// <param name="source"></param>
   void CopyResource(ID3D12Resource *target, ID3D12Resource *source);

#pragma region Set
   void SetCommandList(ID3D12GraphicsCommandList4 *list) { list_ = list; }
   void SetCommandAllocator(ID3D12CommandAllocator *allocator) { allocator_ = allocator; }
   void SetCommandQueue(ID3D12CommandQueue *queue) { commandQueue_ = queue; }
#pragma endregion

   ID3D12GraphicsCommandList4 *GetCommandList() { return list_; }

 private:
   HANDLE waitEvent = 0;

   ID3D12GraphicsCommandList4 *list_ = nullptr;
   ID3D12CommandQueue *commandQueue_ = nullptr;
   ID3D12CommandAllocator *allocator_ = nullptr;

   DXCommandManager() = default;
   ~DXCommandManager() = default;
   DXCommandManager(const DXCommandManager &) = delete;
   DXCommandManager &operator=(const DXCommandManager &) = delete;
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA
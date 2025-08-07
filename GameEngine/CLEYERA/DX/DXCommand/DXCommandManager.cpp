#include "DXCommandManager.h"
#include "../DXManager.h"

using namespace CLEYERA::Base::DX;

DXCommandManager *DXCommandManager::GetInstace() {

   static DXCommandManager instance;
   return &instance;
}

void CLEYERA::Base::DX::DXCommandManager::Init() {
   list_ = DXManager::GetInstance()->GetCommandList();
   commandQueue_ = DXManager::GetInstance()->GetCommandQueue();
}

void CLEYERA::Base::DX::DXCommandManager::OMRenderTargets(const std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> &rtvHandles, const D3D12_CPU_DESCRIPTOR_HANDLE *dsvHandle) {

   if (list_) {
      list_->OMSetRenderTargets(static_cast<UINT>(rtvHandles.size()), rtvHandles.data(), false, dsvHandle);
   }
}

void CLEYERA::Base::DX::DXCommandManager::ClearRenderTargetView(D3D12_CPU_DESCRIPTOR_HANDLE handle, const std::vector<float> &clearColor) {
   if (list_ && clearColor.size() == 4) {
      list_->ClearRenderTargetView(handle, clearColor.data(), 0, nullptr);
   }
}

void CLEYERA::Base::DX::DXCommandManager::ClearDepthStencilView(D3D12_CPU_DESCRIPTOR_HANDLE handle, D3D12_CLEAR_FLAGS flag) {

   if (list_) {
      list_->ClearDepthStencilView(handle, flag, 1.0f, 0, 0, nullptr);
   }
}

void CLEYERA::Base::DX::DXCommandManager::SetViewCommand(int32_t width, int32_t height) {

   D3D12_VIEWPORT viewport = {};

   viewport.Width = float(width);
   viewport.Height = float(height);
   viewport.TopLeftX = 0;
   viewport.TopLeftY = 0;
   viewport.MinDepth = 0.0f;
   viewport.MaxDepth = 1.0f;

   list_->RSSetViewports(1, &viewport);
}

void CLEYERA::Base::DX::DXCommandManager::SetScissorCommand(int32_t width, int32_t height) {

   D3D12_RECT scissorRect{};
   scissorRect.left = 0;
   scissorRect.right = width;
   scissorRect.top = 0;
   scissorRect.bottom = height;

   list_->RSSetScissorRects(1, &scissorRect);
}

void CLEYERA::Base::DX::DXCommandManager::SetDescripterHeap(const std::vector<ID3D12DescriptorHeap *> desc) { list_->SetDescriptorHeaps(static_cast<UINT>(desc.size()), desc.data()); }

void CLEYERA::Base::DX::DXCommandManager::CommandClose() {

   HRESULT hr = list_->Close();
   assert(SUCCEEDED(hr));

   ID3D12CommandList *commandLists[] = {list_};
   commandQueue_->ExecuteCommandLists(1, commandLists);

   UINT64 fenceValue = 1;

   ID3D12Device5 *device = DXManager::GetInstance()->GetDevice();

   ComPtr<ID3D12Fence1> fence = nullptr;
   device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.ReleaseAndGetAddressOf()));

   // Event
   commandQueue_->Signal(fence.Get(), fenceValue);

   if (fence->GetCompletedValue() < fenceValue) {
      HANDLE fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
      assert(fenceEvent != nullptr);
      fence->SetEventOnCompletion(fenceValue, fenceEvent);
      WaitForSingleObject(fenceEvent, INFINITE);
      CloseHandle(fenceEvent);
   }

   // コマンドリセット
   hr = allocator_->Reset();
   assert(SUCCEEDED(hr));
   hr = list_->Reset(allocator_, nullptr);
   assert(SUCCEEDED(hr));
}

void CLEYERA::Base::DX::DXCommandManager::CommandExecute() {
   if (list_) {

      ID3D12CommandList *commandLists[] = {list_};
      commandQueue_->ExecuteCommandLists(1, commandLists);
   }
}

void CLEYERA::Base::DX::DXCommandManager::WaitForIdleGpu() {
   ID3D12Device5 *device = DXManager::GetInstance()->GetDevice();

   ComPtr<ID3D12Fence1> fence;
   device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.ReleaseAndGetAddressOf()));
   UINT64 fenceValue = 1;
   fence->SetEventOnCompletion(fenceValue, waitEvent);
   commandQueue_->Signal(fence.Get(), fenceValue);
   WaitForSingleObject(waitEvent, INFINITE);
}

void CLEYERA::Base::DX::DXCommandManager::SetDescripter(std::vector<ID3D12DescriptorHeap *> desc) { list_->SetDescriptorHeaps(UINT(desc.size()), desc.data()); }

void CLEYERA::Base::DX::DXCommandManager::Barrier(const D3D12_RESOURCE_BARRIER &barrier) { list_->ResourceBarrier(1, &barrier); }

void CLEYERA::Base::DX::DXCommandManager::ComputeRootSignature(ID3D12RootSignature *root) { list_->SetComputeRootSignature(root); }

void CLEYERA::Base::DX::DXCommandManager::ComputeDescripterTable(UINT num, D3D12_GPU_DESCRIPTOR_HANDLE handle) { list_->SetComputeRootDescriptorTable(num, handle); }

void CLEYERA::Base::DX::DXCommandManager::GraphicsDescripterTable(UINT num, D3D12_GPU_DESCRIPTOR_HANDLE handle) { list_->SetGraphicsRootDescriptorTable(num, handle); }

void CLEYERA::Base::DX::DXCommandManager::DispachRay(const D3D12_DISPATCH_RAYS_DESC &desc) { list_->DispatchRays(&desc); }

void CLEYERA::Base::DX::DXCommandManager::GraphicsCommandCall(UINT number, ID3D12Resource *buf) {
   if (list_) {
      list_->SetGraphicsRootConstantBufferView(number, buf->GetGPUVirtualAddress());
   }
}

void CLEYERA::Base::DX::DXCommandManager::GraphicsRootSignature(ID3D12RootSignature *root) {

   if (list_) {
      list_->SetGraphicsRootSignature(root);
   }
}

void CLEYERA::Base::DX::DXCommandManager::GraphicsPipelineState(ID3D12PipelineState *state) {
   if (list_) {
      list_->SetPipelineState(state);
   }
}

void CLEYERA::Base::DX::DXCommandManager::VBCommandCall(const std::vector<D3D12_VERTEX_BUFFER_VIEW> &view) {

   if (list_) {
      list_->IASetVertexBuffers(0, UINT(view.size()), view.data());
   }
}

void CLEYERA::Base::DX::DXCommandManager::IBCommandCall(const std::vector<D3D12_INDEX_BUFFER_VIEW> &view) {

   if (list_) {
      list_->IASetIndexBuffer(view.data());
   }
}

void CLEYERA::Base::DX::DXCommandManager::SetTopology(D3D_PRIMITIVE_TOPOLOGY type) {

   if (list_) {
      list_->IASetPrimitiveTopology(type);
   }
}

void CLEYERA::Base::DX::DXCommandManager::DrawIndexCall(UINT num) {

   if (list_) {
      list_->DrawIndexedInstanced(num, 1, 0, 0, 0);
   }
}

void CLEYERA::Base::DX::DXCommandManager::DrawCall(UINT vertNum, UINT instanceid) {

   if (list_) {
      list_->DrawInstanced(vertNum, instanceid, 0, 0);
   }
}

void CLEYERA::Base::DX::DXCommandManager::CopyResource(ID3D12Resource *target, ID3D12Resource *source) {
   if (list_) {

      list_->CopyResource(target, source);
   }
}

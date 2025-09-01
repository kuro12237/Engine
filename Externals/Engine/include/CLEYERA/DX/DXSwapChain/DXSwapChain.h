#pragma once
#include "../DXBufferResource/DXBufferResource.h"
#include "../DXComponent.h"

#include "../DXCommand/DXCommandManager.h"

#include "../DXDescripter/DXDescripterManager.h"

namespace CLEYERA {
namespace Base {
namespace DX {

using Microsoft::WRL::ComPtr;

/// <summary>
///
/// </summary>
class DXSwapChain : public DXComponent {
 public:
   DXSwapChain(const std::string &name) : DXComponent(name) {};
   ~DXSwapChain() = default;

   void Create() override;

   void RegisterRTV();

   void Begin();

   void SwapChainResourceState(const D3D12_RESOURCE_BARRIER &barrir);

   /// <summary>
   /// 描画されてるrtvにコピーする
   /// </summary>
   /// <returns></returns>
   void RTVCopyBuf(ID3D12Resource* buf);

#pragma region Get

   IDXGISwapChain4 *GetSwapChain() { return swapChain_.Get(); }

   DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc() { return swapChainDesc_; }
   D3D12_RENDER_TARGET_VIEW_DESC GetRTVDesc() { return rtvDesc_; }

   ID3D12Resource *GetSwapChainResource(size_t index) const { return resources_[index]->GetResource(); }
   size_t GetSwapChainCount() { return swapChainCount_; }

#pragma endregion

 private:
   /// <summary>
   /// swapChain
   /// </summary>
   void CreateResources();

   static const size_t swapChainCount_ = 2;
   DXGI_SWAP_CHAIN_DESC1 swapChainDesc_{};
   ComPtr<IDXGISwapChain4> swapChain_ = nullptr;

   std::array<std::unique_ptr<DXBufferResource<uint32_t>>, swapChainCount_> resources_;

   DXCommandManager *commandManager_ = nullptr;
   DXDescripterManager *descripterManager_ = nullptr;

   D3D12_RENDER_TARGET_VIEW_DESC rtvDesc_{};

   UINT backBufferIndex_ = 0;
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA
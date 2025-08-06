#include "ImGuiCommon.h"

CLEYERA::Utility::ImGuiCommon::ImGuiCommon() {

   winApp_ = Base::Win::WinApp::GetInstance();
   dxManager_ = Base::DX::DXManager::GetInstance();
   descripterManager_ = Base::DX::DXDescripterManager::GetInstance();
}

CLEYERA::Utility::ImGuiCommon::~ImGuiCommon() {

   ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX12_Shutdown();
   ImGui::DestroyContext();

}

void CLEYERA::Utility::ImGuiCommon::Init() {

   srvIndex_ = descripterManager_->SRVAddPtr();
   ID3D12DescriptorHeap *descripter = descripterManager_->GetSRV().lock()->GetDescripter();
   ID3D12Device5 *device = dxManager_->GetDevice();
   int swapBufferCount = dxManager_->GetSwapChain().lock()->GetSwapChainDesc().BufferCount;
   DXGI_FORMAT format = dxManager_->GetSwapChain().lock()->GetRTVDesc().Format;

   commandList_ = dxManager_->GetCommandList();

   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGui::StyleColorsDark();

   ImGui_ImplWin32_Init(winApp_->GetHWND());
   ImGui_ImplDX12_Init(device, swapBufferCount, format, descripter, descripterManager_->GetSRV().lock()->GetDescripter()->GetCPUDescriptorHandleForHeapStart(), descripterManager_->GetSRV().lock()->GetDescripter()->GetGPUDescriptorHandleForHeapStart());
}

void CLEYERA::Utility::ImGuiCommon::Begin() {
   ImGui_ImplDX12_NewFrame();
   ImGui_ImplWin32_NewFrame();
   ImGui::NewFrame();
}

void CLEYERA::Utility::ImGuiCommon::Render() {

   ImGui::Render();
   ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList_);
}

void CLEYERA::Utility::ImGuiCommon::End() {
  ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList_);
}

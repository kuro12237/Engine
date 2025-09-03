#pragma once
#include "../../pch/Pch.h"
#include"../../DX/DXBufferResource/DXBufferResource.h"

namespace CLEYERA {

namespace Graphics {

namespace system {

class TexData {
 public:
   TexData() {};
   ~TexData() {};

   void SetTexBuf(std::unique_ptr<Base::DX::DXBufferResource<uint32_t>> texBuf) { texBuf_ = std::move(texBuf); }
   void SetSize(const Math::Vector::Vec2 &size) { size_ = size; }
   void SetTexHandle(uint32_t handle) { texHandle_ = handle; }
   void SetTexPath(const std::string &path) { texPath_ = path; }

   uint32_t GetTexHandle() const { return texHandle_; }
   const std::string &GetTexPath() const { return texPath_; }
   const Math::Vector::Vec2 &GetSize() const { return size_; }

   uint32_t GetSrvIndex() { return uint32_t(texBuf_->GetSRVIndex()); }

 private:
   uint32_t texHandle_ = 0;
   std::string texPath_ = "NONE";

   Math::Vector::Vec2 size_ = {};
   std::unique_ptr<Base::DX::DXBufferResource<uint32_t>> texBuf_ = nullptr;
};

} // namespace system

} // namespace Graphics

} // namespace CLEYERA
#pragma once
#include "DX/DXBufferResource/DXBufferResource.h"
#include "DX/DXManager.h"
#include "IMaterial3d.h"

namespace CLEYERA {

namespace Model3d {
namespace Material {

template <typename T> class MaterialBase : public IMaterial {
public:
  MaterialBase() = default;
  ~MaterialBase() = default;

  void Bind(const size_t &index) override;

  void Create()override;

  void Update()override;

  void SetParam(T *p) { param_ = p; }

private:
  T *param_;

protected:
  std::unique_ptr<CLEYERA::Base::DX::DXBufferResource<T>> buf_ = nullptr;
};

template <typename T> inline void MaterialBase<T>::Bind(const size_t &index) {

	UINT num = static_cast<UINT>(index);

  buf_->GraphicsCommand(num);
}
template <typename T> inline void MaterialBase<T>::Create() {

  auto device = CLEYERA::Base::DX::DXManager::GetInstance()->GetDevice();
  buf_ = std::make_unique<CLEYERA::Base::DX::DXBufferResource<T>>();
  buf_->SetDevice(device);
  buf_->Init();
  buf_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
}
template <typename T> inline void MaterialBase<T>::Update() {

  buf_->Map();
  buf_->SetParam(*param_);
  buf_->UnMap();
}
} // namespace Material
} // namespace Model
} // namespace CLEYERA
#pragma once

#include "../Game3dObject.h"

namespace CLEYERA {

namespace Model3d {

template <typename T> class InstancingBase {
public:
  InstancingBase() {
    command_ = CLEYERA::Base::DX::DXCommandManager::GetInstace();
  };
  virtual ~InstancingBase() {};

  virtual void Init(uint32_t max = 1) = 0;

  virtual void Update() = 0;

  void Command(uint32_t num) {
    command_->GraphicsDescripterTable(
        num, Base::DX::DXDescripterManager::GetInstance()->GetSRVGPUHandle(
               buf_->GetSRVIndex()));
  };

  void SetWorldData(const T *data, uint32_t index) { data_[index] = data; }

  void DelateData(uint32_t index) { data_[index] = nullptr; }

private:
  Base::DX::DXCommandManager *command_;

protected:
  void Create(int32_t max);
  void Map();

  std::unique_ptr<CLEYERA::Base::DX::DXBufferResource<T>> buf_ = nullptr;
  std::vector<const T *> data_;
};

template <typename T> inline void InstancingBase<T>::Create(int32_t max) {
  auto device_ = Base::DX::DXManager::GetInstance()->GetDevice();
  this->data_.resize(max);
  buf_ = std::make_unique<CLEYERA::Base::DX::DXBufferResource<T>>();
  buf_->Init(max);
  buf_->SetDevice(device_);
  // バッファの作成
  buf_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
  buf_->CreateVertexBufferView();

  buf_->RegisterSRV();
}

template <typename T> inline void InstancingBase<T>::Map() {
  buf_->Map();
  buf_->SetParam(data_);
  buf_->UnMap();
}

} // namespace Model3d
} // namespace CLEYERA
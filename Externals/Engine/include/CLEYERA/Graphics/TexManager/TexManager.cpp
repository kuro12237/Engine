#include "TexManager.h"

void CLEYERA::Manager::TexManager::Init() { CoInitializeEx(0, COINIT_MULTITHREADED); }

void CLEYERA::Manager::TexManager::Finalize() {

   texs_.erase(texs_.begin(), texs_.end());

   CoUninitialize();
}

uint32_t CLEYERA::Manager::TexManager::LoadPngTex(const std::string &path) {

   std::string filePath = path;

   if (isUseDirectoryPath_) {
      filePath = DirectoryDilePath_ + filePath + ".png";
   }

   isUseDirectoryPath_ = true;

   // すでに読み込まれているかチェック
   auto it = texs_.find(filePath);
   if (it != texs_.end()) {
     return it->second->GetTexHandle(); // すでに存在するならそのハンドルを返す
   }


   // MipImageを作る
   DirectX::ScratchImage mipImages = CreateMipImage(filePath);
   const DirectX::TexMetadata &metadata = mipImages.GetMetadata();

   std::shared_ptr<Graphics::system::TexData> data = std::make_shared<Graphics::system::TexData>();
   std::unique_ptr<Base::DX::DXBufferResource<uint32_t>> buf = std::make_unique<Base::DX::DXBufferResource<uint32_t>>();

   buf->SetDevice(Base::DX::DXManager::GetInstance()->GetDevice());
   buf->Init(1);

   D3D12_RESOURCE_DESC resourceDesc{};
   resourceDesc.Width = UINT(metadata.width);
   resourceDesc.Height = UINT(metadata.height);
   resourceDesc.MipLevels = UINT16(metadata.mipLevels);
   resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize);
   resourceDesc.Format = metadata.format;
   resourceDesc.SampleDesc.Count = 1;
   resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension);
   D3D12_HEAP_PROPERTIES heapProperties{};
   heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;

   buf->CreateBuffer(heapProperties, D3D12_HEAP_FLAG_NONE, resourceDesc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr);

   //  MipImageを登録
   std::unique_ptr<Base::DX::DXBufferResource<int64_t>> intermediateResource = UpLoadTexData(buf->GetResource(), mipImages);
   Base::DX::DXCommandManager::GetInstace()->CommandClose();

   D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
   srvDesc.Format = metadata.format;
   srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
   srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
   srvDesc.Texture2D.MipLevels = UINT(metadata.mipLevels);
   buf->RegisterSRV(srvDesc);

   data->SetTexBuf(std::move(buf));
   data->SetTexPath(filePath);
   data->SetTexHandle(texHandle_);

   Math::Vector::Vec2 size = {float(metadata.width), float(metadata.height)};
   data->SetSize(size);

   this->texs_[filePath] = std::move(data);
   int32_t handle = texHandle_;
   texHandle_++;
   return handle;
}

std::weak_ptr<CLEYERA::Graphics::system::TexData> CLEYERA::Manager::TexManager::GetTexData(uint32_t handle) {

   for (auto &[key, data] : texs_) {
      if (data->GetTexHandle() == handle) {
         return data;
      }
   }
   assert(0);
   return std::weak_ptr<CLEYERA::Graphics::system::TexData>();
}

std::unique_ptr<CLEYERA::Base::DX::DXBufferResource<int64_t>> CLEYERA::Manager::TexManager::UpLoadTexData(ComPtr<ID3D12Resource> resource, const DirectX::ScratchImage &mipImage) {

   ID3D12Device *device = Base::DX::DXManager::GetInstance()->GetDevice();
   ID3D12GraphicsCommandList *command = Base::DX::DXCommandManager::GetInstace()->GetCommandList();

   std::vector<D3D12_SUBRESOURCE_DATA> subresources;
   DirectX::PrepareUpload(device, mipImage.GetImages(), mipImage.GetImageCount(), mipImage.GetMetadata(), subresources);
   uint64_t intermediateSize = GetRequiredIntermediateSize(resource.Get(), 0, UINT(subresources.size()));

   std::unique_ptr<Base::DX::DXBufferResource<int64_t>> intermediaResource = std::make_unique<Base::DX::DXBufferResource<int64_t>>();
   intermediaResource->SetDevice(Base::DX::DXManager::GetInstance()->GetDevice());
   intermediaResource->Init(intermediateSize);
   intermediaResource->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);

   UpdateSubresources(command, resource.Get(), intermediaResource->GetResource(), 0, 0, UINT(subresources.size()), subresources.data());

   D3D12_RESOURCE_BARRIER barrier;
   barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
   barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
   barrier.Transition.pResource = resource.Get();
   barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
   barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
   barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;
   command->ResourceBarrier(1, &barrier);
   return std::move(intermediaResource);
}

DirectX::ScratchImage CLEYERA::Manager::TexManager::CreateMipImage(const std::string &filePath) {
   // テクスチャファイルを読み込みプログラムで扱えるようにする
   DirectX::ScratchImage image{};
   std::wstring filePathW = ConvertString(filePath);
   HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
   assert(SUCCEEDED(hr));
   // ミップマップの作成
   DirectX::ScratchImage mipImage{};
   hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImage);
   return mipImage;
}

DirectX::ScratchImage CLEYERA::Manager::TexManager::CreateDDSMipImage([[maybe_unused]] const std::string &filePath) { return DirectX::ScratchImage(); }

#pragma once
#include "../../DX/DXManager.h"
#include "TexData.h"

namespace CLEYERA {

namespace Manager {

class TexManager {
 public:
   static TexManager *GetInstance() {
      static TexManager instance;
      return &instance;
   }

   void Init();

   void Finalize();

   uint32_t LoadPngTex(const std::string &path);

   std::weak_ptr<Graphics::system::TexData>GetTexData(uint32_t handle);

   void UnUsedFilePath() { isUseDirectoryPath_ = false; };


 private:
   [[nodiscard]]
   std::unique_ptr<Base::DX::DXBufferResource<int64_t>> UpLoadTexData(ComPtr<ID3D12Resource> resource, const DirectX::ScratchImage &mipImage);

   /// <summary>
   /// MipImageを作製
   /// </summary>
   /// <param name="filePath"></param>
   /// <returns></returns>
   static DirectX::ScratchImage CreateMipImage(const std::string &filePath);

   /// <summary>
   /// DDSのMipImageを作製
   /// </summary>
   /// <param name="filePath"></param>
   /// <returns></returns>
   static DirectX::ScratchImage CreateDDSMipImage(const std::string &filePath);

   uint32_t texHandle_ = 0;

   std::map<std::string, std::shared_ptr<Graphics::system::TexData>> texs_;

   bool isUseDirectoryPath_ = true;
   std::string DirectoryDilePath_ = "Resources/Tex/";

#pragma region single

   TexManager() = default;
   ~TexManager() = default;
   TexManager(const TexManager &) = delete;
   TexManager &operator=(const TexManager &) = delete;

#pragma endregion
};

} // namespace Manager

} // namespace CLEYERA

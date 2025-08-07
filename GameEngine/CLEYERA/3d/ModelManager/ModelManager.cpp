#include "ModelManager.h"

CLEYERA::Manager::ModelManager *CLEYERA::Manager::ModelManager::GetInstance() {
   static ModelManager instance;
   return &instance;
}

uint32_t CLEYERA::Manager::ModelManager::LoadModel(const std::string &directory, const std::string fileName) {
   Assimp::Importer importer;
   std::string file =  directory + "/" + fileName + ".obj";

   //読み込み済みの場合
   if (datas_.find(file) != datas_.end()) {
      return datas_[file]->GetHandle();
   }

   const aiScene *scene = importer.ReadFile(file.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
   assert(scene->HasMeshes());

   std::unique_ptr<Model3d::system::Model3dPool> data = std::make_unique<Model3d::system::Model3dPool>();

   std::shared_ptr<Model3d::Model> model = std::make_shared<Model3d::Model>();

   for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
      aiMesh *mesh = scene->mMeshes[meshIndex];
      assert(mesh->HasNormals());
      assert(mesh->HasTextureCoords(0));
      // 頂点作成
      model->CreateMesh(mesh);
   }

   // テクスチャ作成
   // materialの解析
   std::string path = "";
   uint32_t texHandle = 0;
   for (uint32_t materialIndex = 0; materialIndex < scene->mNumMaterials; materialIndex++) {
      aiMaterial *material = scene->mMaterials[materialIndex];
      if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
         aiString texFilePath;
         material->GetTexture(aiTextureType_DIFFUSE, 0, &texFilePath);

         path = directory + "/" +  texFilePath.C_Str();
         texManager_->UnUsedFilePath();
         texHandle = texManager_->LoadPngTex(path);
      }
   }

   model->Init();
   data->SetHandle(handle_);
   model->SetTexHandle(texHandle);
   data->SetModel(model);

   datas_[file] = std::move(data);

   return handle_++;
}


std::weak_ptr<CLEYERA::Model3d::Model> CLEYERA::Manager::ModelManager::GetModel(uint32_t key) {

   for (const auto &data : datas_) {

      auto &it = data.second;

      if (it->GetHandle() == key) {

         return it->GetModel();
      }
   }

   assert(false);

   return std::weak_ptr<CLEYERA::Model3d::Model>();
}

void CLEYERA::Manager::ModelManager::Init() { texManager_ = TexManager::GetInstance();
}

void CLEYERA::Manager::ModelManager::Finalize() { datas_.clear(); }

#include "TestObject.h"

void TestObj::Init() {

  this->category_ = VAR_NAME(TestObj);
  uint32_t modelHandle = modelManager_->LoadModel(
      "Resources/Model/system/human", "walk",
      CLEYERA::Manager::ModelManager::LoadModelData::GLTF);
  objectManager_->GetCategoryData(category_).ChangeModelData(modelHandle);

  this->isTerrainHit_ = false;
  this->isGravity_ = false;
}

void TestObj::Update() {}

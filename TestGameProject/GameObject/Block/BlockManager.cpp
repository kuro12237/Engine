#include "BlockManager.h"

void BlockManager::Init() {

  BlockSizeData block;
  block.name = VAR_NAME(NormalBlock);
  block.size = this->GetCategorySizeFunc_(block.name);
  this->CreateBlock<NormalBlock>(block);

  auto objM = CLEYERA::Manager::ObjectManager::GetInstance();
  objM->GetCategoryData(block.name)
      .ChangeDrawMode(CLEYERA::Util::system::InstancingObjectData::DrawMode::
                          Normal_MODEL3d);
}

void BlockManager::Update() {}
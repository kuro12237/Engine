#include "GameScene.h"

void GameScene::Init() {
  auto objM = CLEYERA::Manager::ObjectManager::GetInstance();

  loader_ = std::make_unique<SceneLoader>();
  loader_->LoadFile("GameScene");

  sun_ = std::make_unique<Sun>();
  sun_->Init();

  player_ = std::make_unique<PlayerManager>();
  player_->Init();

  blocks_ = std::make_unique<BlockManager>();
  blocks_->SetGetCategorySizeFunc(std::bind(&SceneLoader::GetCategoryObjectSize,
                                            loader_.get(), std::placeholders::_1));
  blocks_->Init();

  loader_->SettingData();

  uint32_t model = CLEYERA::Manager::ModelManager::GetInstance()->LoadModel(
      "Resources/Model/Terrain/", "Terrain");

  auto terrain = CLEYERA::Manager::Terrain::GetInstance();
  terrain->Init();
  //terrain->ChengeData(model);
}

void GameScene::Update(CLEYERA::Manager::SceneManager *ins) {
  player_->Update();
  sun_->Update();
  auto obj = CLEYERA::Manager::ObjectManager::GetInstance();
}

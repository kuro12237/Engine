#pragma once
#include "CLEYERA.h"

#include <fstream>

#include"../GameObject/UtilGameObject/UtilGameObject.h"

struct SceneObjData {

  Math::Vector::Vec3 scale = {};
  Math::Vector::Vec3 rotate = {};
  Math::Vector::Vec3 translate = {};

  std::string modelDirectoryPath = "";
  std::string modelName = "";
  uint32_t modeHandle_ = 0;
  std::vector<std::string> parentObjName_;
  bool isGravity_ = true;
  bool isTerrainHit = true;
};

class SceneLoader {
public:
  SceneLoader() {};
  ~SceneLoader() {};

  void LoadFile(std::string file);

  std::vector<std::weak_ptr<UtilGameObject>> SettingData();

  size_t GetCategoryObjectSize(std::string category){
    return categoryObjectSize_[category];
  };

private:
  SceneObjData LoadobjData(nlohmann::json object, SceneObjData data = {},
                           std::string name = "");
  
  std::string RemoveNumberSuffix(const std::string &key);

  const std::string directoryPath_ = "Resources/SceneData/";
  nlohmann::json deserialized = nullptr;

  std::map<std::string, SceneObjData> objDatas_;
  std::map<std::string, size_t> categoryObjectSize_;
};

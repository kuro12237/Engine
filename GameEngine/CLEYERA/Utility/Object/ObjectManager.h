#pragma once
#include "3d/Instancing/InstancingMaterial.h"
#include "3d/Instancing/InstancingWorld.h"
#include "Compornent/ObjectCompornent.h"
#include "Graphics/RasterPipline/RasterPiplineManager.h"
#include "Utility/PhysicsForces/GravityManager.h"
#include "Utility/Terrain/Terrain.h"

namespace CLEYERA {

namespace Util {

namespace system {

struct InstancingObjectData {
    
  using DrawMode = Graphics::RasterPipline_Mode3d;

  size_t max = 1;
  uint32_t modelHandle = 0;
  DrawMode drawMode_ = DrawMode::DF_MODEL3d;

  std::weak_ptr<Model3d::Model> model;

  std::unique_ptr<Model3d::InstancingMaterial> MaterialIns = nullptr;
  std::map<std::string, const Model3d::Material::ColorMaterialData *>
      MaterialData;
  std::unique_ptr<Model3d::InstancingWorld> worldIns = nullptr;
  std::map<std::string, const forWorldMat *> worldData;

  void ChangeModelData(uint32_t modelHandle_);
  void ChangeDrawMode(DrawMode mode) { drawMode_ = mode; }
};

} // namespace system
} // namespace Util

namespace Manager {

/// <summary>
/// オブジェクトのJson型
/// </summary>
struct ObjectNumData {

  std::string key;
  uint32_t objNum;

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(ObjectNumData, key, objNum);
};

/// <summary>
/// Object管理クラス
/// </summary>
class ObjectManager {
public:
  static ObjectManager *GetInstance() {
    static ObjectManager instance;
    return &instance;
  }

  void Update();

  void ImGuiUpdate();

  void Clear() {
    objects_.clear(), unUseObjsName_.clear();
    instancingData_.clear();
  }

  void Draw();

  /// <summary>
  /// オブジェクトの合計数を読み込む関数
  /// </summary>
  void LoadObjectData(const std::string &file);

  /// <summary>
  /// オブジェクトを作成(jsonで確保した配列に作成)
  /// </summary>
  template <typename T>
  std::weak_ptr<T>
  CreateObject(const std::string &category,
               std::shared_ptr<Component::ObjectComponent> obj) {

    this->ObjectRegister(category, 128, obj);
    return std::dynamic_pointer_cast<T>(obj);
  };

  void DeleteObject(std::weak_ptr<Component::ObjectComponent> obj);

  const std::map<std::string,
           std::map<std::string, std::shared_ptr<Component::ObjectComponent>>>
  &GetObjects() const {
    return objects_;
  }

  const std::map<std::string, Util::system::InstancingObjectData>
  &GetInstancingData() const {
    return instancingData_;
  }

  Util::system::InstancingObjectData &GetCategoryData(const std::string &name) {
    return instancingData_[name];
  }

private:
  std::map<std::string,
           std::map<std::string, std::shared_ptr<Component::ObjectComponent>>>
      objects_;
  std::map<std::string, Util::system::InstancingObjectData> instancingData_;

  std::map<std::string, std::vector<std::string>> unUseObjsName_;

  void ObjectRegister(const std::string &category, const size_t &size,
                      std::shared_ptr<Component::ObjectComponent> obj);

  void CreateInstancing(const std::string &category, uint32_t size);

  int ExtractNumber(const std::string &key);

#pragma region Singleton

  ObjectManager() = default;
  ~ObjectManager() = default;
  ObjectManager(const ObjectManager &) = delete;
  ObjectManager &operator=(const ObjectManager &) = delete;

#pragma endregion
};

} // namespace Manager
} // namespace CLEYERA
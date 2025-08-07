#pragma once
#include "../3d/Game3dObject.h"
#include "../3d/ModelManager/ModelManager.h"
#include "../Utility/RenderManager/RenderManager.h"

#include "../Utility/Input/InputManager.h"
#include "Utility/Flame/Flame.h"

#include "JsonCompornent.h"

namespace CLEYERA {

namespace Util {

namespace Collider {

enum class ColliderType;
class Collider;
class OBBCollider;
class AABBCollider;

} // namespace Collider
} // namespace Util

namespace Manager {
class ObjectManager;
class ColliderSystem;
} // namespace Manager

namespace Component {

/// <summary>
/// objectのコンポーネント基本継承
/// </summary>
class ObjectComponent {
public:
  ObjectComponent();
  virtual ~ObjectComponent() {};

  enum class OBJ_MODE {
    SPAWN = 0, // 生成直後
    ACTIVE,    // 通常動作中
    INACTIVE,  // 非アクティブ（更新/描画なし）
    PAUSE,     // 一時停止
    REMOVE,    // 削除予定（DeleteObjectと連携）

  };

  virtual void Init() = 0;
  virtual void Update() = 0;
  virtual void Finalize() {};
  /// <summary>
  /// IMGui仮想関数上書き推奨
  /// </summary>
  virtual void ImGuiUpdate();

  /// <summary>
  /// 加速度,veloの更新
  /// </summary>
  void TransformUpdate();

  /// <summary>
  /// 重力更新
  /// </summary>
  /// <param name="g"></param>
  void GravityUpdate(const float &g);

  /// <summary>
  /// 地形の当たり判定呼び出し
  /// </summary>
  /// <param name="pos"></param>
  void TerrainHit(const Math::Vector::Vec3 &pos);

  void GameObjectUpdate() { this->gameObject_->Update(); };

#pragma region Get
  const std::string &GetName() const { return name_; }
  const std::string &GetCategory() const { return category_; }
  const OBJ_MODE &GetMode() const { return mode_; }

  std::weak_ptr<Model3d::Game3dObject> GetGameObject() { return gameObject_; }
  std::weak_ptr<Util::Collider::Collider> GetCollider() { return collider_; }
  Math::Vector::Vec3 &GetTranslate() { return translate_; }
  Math::Matrix::Mat4x4 GetMatWorld() const {
    return Math::Matrix::Func::AffineMatrix(scale_, rotate_, translate_);
  }

  /// <summary>
  /// jsonパラメータのGet
  /// </summary>
  template <typename T> T GetValue(const std::string &name) {
    return jsonSystem_->GetValue<T>(name);
  }

  bool GetIsGravity() { return isGravity_; }
  bool GetIsTerrainHit() { return isTerrainHit_; }
#pragma endregion

#pragma region Set

  void SetName(std::string name) { name_ = name; }
  void SetCategory(const std::string &category) { category_ = category; }
  void SetMode(const OBJ_MODE mode) { mode_ = mode; }

#pragma region param
  void SetScale(const Math::Vector::Vec3 &v) { scale_ = v; }
  void SetRotate(const Math::Vector::Vec3 &v) { rotate_ = v; }
  void SetTranslate(const Math::Vector::Vec3 &v) { translate_ = v; }
  void SetForce(const Math::Vector::Vec3 &v) { force_ = v; }

  /// <summary>
  /// 使う場合にtrue
  /// </summary>
  void SetIsGravity(bool f = true) { isGravity_ = f; }

  /// <summary>
  /// 使う場合にtrue
  /// </summary>
  void SetIsTerrainHit(bool f = true) { isTerrainHit_ = f; }

#pragma endregion
  void SetModelHandle(uint32_t handle) {
    modelHandle_ = handle;
    gameObject_->ChangeModel(handle);
  }

  /// <summary>
  /// jsonパラメータSet
  /// </summary>
  template <typename T> void SetValue(const std::string &name, T t) {
    jsonSystem_->SetValue<T>(name, t);
  }
#pragma endregion

private:
  uint32_t modelHandle_ = 0;

protected:
  using OBJ_MODE = CLEYERA::Component::ObjectComponent::OBJ_MODE;

  /// <summary>
  /// 基礎機能表示(内容Transform,json,collider)
  /// </summary>
  void BaseParamImGuiDisply();

  Manager::ModelManager *modelManager_ = nullptr;
  Manager::ObjectManager *objectManager_ = nullptr;
  Manager::RenderManager *renderManager_ = nullptr;
  Manager::ColliderSystem *colliderSystem_ = nullptr;
  Manager::InputManager *inputManager_ = nullptr;

  using ColliderType = Util::Collider::ColliderType;

  /// <summary>
  /// コライダー作成
  /// </summary>
  /// <param name="type"></param>
  void CreateCollider(ColliderType type);

  /// <summary>
  /// jsonの作成
  /// </summary>
  void CreateJsonSystem(const std::string &fileGroupName);

  std::string category_ = "";
  std::string name_ = "";

  Math::Vector::Vec3 scale_ = {2.0f, 2.0f, 2.0f};
  Math::Vector::Vec3 rotate_ = {};
  Math::Vector::Vec3 translate_ = {};

  Math::Vector::Vec3 velocity_ = {};
  Math::Vector::Vec3 force_ = {};
  float friction_ = 0.5f;
  float mass_ = 1.0f;
  float bounceFactor_ = 0.5f;

  // 当たり判定
  std::shared_ptr<Util::Collider::Collider> collider_ = nullptr;
  // jsonのシステム
  std::shared_ptr<Component::JsonCompornent> jsonSystem_ = nullptr;
  // WorldTransform,GameObject等のクラス
  std::shared_ptr<Model3d::Game3dObject> gameObject_ = nullptr;

  OBJ_MODE mode_ = OBJ_MODE::SPAWN;

  bool isGravity_ = true;
  bool isTerrainHit_ = true;
};
} // namespace Component
} // namespace CLEYERA
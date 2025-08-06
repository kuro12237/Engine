#pragma once
#include "2d/Sprite.h"
#include "Utility/Json/GlobalVariables.h"
#include "Utility/World/WorldTransform.h"

#include "JsonCompornent.h"

class SpriteComponent : public CLEYERA::Util::WorldTransform,
                        public CLEYERA::Component::JsonCompornent {
public:
  SpriteComponent() {
    texManager_ = CLEYERA::Manager::TexManager::GetInstance();
    globalVariables_ = CLEYERA::Manager::GlobalVariables::GetInstance();
  };
  virtual ~SpriteComponent() {};

#pragma region VirtualFunc

  virtual void Init() = 0;
  virtual void Update() = 0;
  virtual void ImGuiUpdate();
#pragma endregion

  /// <summary>
  /// 描画
  /// </summary>
  void Draw();

  void Create();

  std::string GetName() { return name_; }
  void SetName(const std::string &name) { name_ = name; }

private:
protected:
  /// <summary>
  /// jsonの作成
  /// </summary>
  void CreateJsonSystem(const std::string &fileGroupName = "");

  std::string name_ = "";

  CLEYERA::Manager::TexManager *texManager_ = nullptr;
  CLEYERA::Manager::GlobalVariables *globalVariables_ = nullptr;

  std::shared_ptr<CLEYERA::Sprite2d::Sprite> sprite_;

  Math::Vector::Vec3 scale_ = {1.0f, 1.0f, 1.0f};
  Math::Vector::Vec3 rotate_ = {};
  Math::Vector::Vec3 translate_ = {};

  Math::Vector::Vec2 size = {1280.0f, 1280.0f};
  Math::Vector::Vec2 anker = {0.5f, 0.5f};

  Math::Vector::Vec2 LeftTop = {0.0f, 1.0f};
  Math::Vector::Vec2 RightTop = {1.0f, 1.0f};
  Math::Vector::Vec2 LeftBottom = {0.0f, 0.0f};
  Math::Vector::Vec2 RightBottom = {1.0f, 0.0f};

  uint32_t handle_ = 0;
};

#pragma once

namespace CLEYERA {

namespace Manager {
class SceneManager;
};

namespace Component {

/// <summary>
/// シーン継承クラス
/// </summary>
class SceneComponent {
public:
  SceneComponent() {};
  virtual ~SceneComponent() {};

  virtual void Init() = 0;
  virtual void Update(CLEYERA::Manager::SceneManager *ins) = 0;
  virtual void ImGuiUpdate() {};
  virtual void Draw2d() {};
  virtual void Finalize() {};

private:
};

} // namespace Component
} // namespace CLEYERA

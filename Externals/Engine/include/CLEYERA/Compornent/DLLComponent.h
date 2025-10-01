#pragma once

#include "pch/Pch.h"

namespace CLEYERA {

namespace Component {

struct DLLComponentData {
  virtual void Init() = 0;
  virtual void Update() = 0;
  virtual void Shutdown() = 0;
};

extern "C" {
__declspec(dllexport) DLLComponentData *CreateData();
__declspec(dllexport) void DestroyData(DLLComponentData *data);
}

class DLLComponent {
public:
  DLLComponent() {};
  virtual ~DLLComponent() {};

  void LoadDLL(const std::string &path);

private:

protected:
  std::filesystem::file_time_type lastWriteTime;

  std::function<void()> InitFunc = nullptr;
  std::function<void()> UpdateFunc = nullptr;

  HMODULE dll = nullptr;
  std::function<CLEYERA::Component::DLLComponentData *()> create;
  std::function<void(CLEYERA::Component::DLLComponentData *)> destroy;

  
};

} // namespace Component
} // namespace CLEYERA
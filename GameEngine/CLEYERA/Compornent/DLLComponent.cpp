#include "DLLComponent.h"

void CLEYERA::Component::DLLComponent::LoadDLL(const std::string &path) {
  std::shared_ptr<CLEYERA::Component::DLLComponentData> compo;

  if (dll) {
    if (compo) {
      compo->Shutdown();
      //destroy(compo);
      compo = nullptr;
    }
    FreeLibrary(dll);
  }

  dll = LoadLibraryA(path.c_str());
  if (!dll) {
    std::cerr << "DLL load failed\n";
    return;
  }

  using CreateFuncRaw = CLEYERA::Component::DLLComponentData *(*)();
  using DestroyFuncRaw = void (*)(CLEYERA::Component::DLLComponentData *);

  auto c = (CreateFuncRaw)GetProcAddress(dll, "CreateData");
  auto d = (DestroyFuncRaw)GetProcAddress(dll, "DestroyData");


  create = c;
  destroy = d;
  InitFunc = [compo]() { compo->Init(); };
  UpdateFunc = [compo]() { compo->Update(); };
}

#include "JsonCompornent.h"

void CLEYERA::Component::JsonCompornent::CreateJson(const std::string& name, const std::string &FileGroupName, Manager::GlobalVariables::ResourcesGroupDirectory type) {

   p_name_ = &name;
   globalVariables_ = Manager::GlobalVariables::GetInstance();

   globalVariables_->CreateGroup(type, name,FileGroupName);

}

void CLEYERA::Component::JsonCompornent::JsonImGuiUpdate() { globalVariables_->ImGuiUpdate(*p_name_); }

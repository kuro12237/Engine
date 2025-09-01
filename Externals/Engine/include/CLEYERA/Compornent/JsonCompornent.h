#pragma once
#include "Utility/Json/GlobalVariables.h"

namespace CLEYERA {

namespace Component {

class JsonCompornent {
 public:
   JsonCompornent() {};
   virtual ~JsonCompornent() {};

   void CreateJson(const std::string &name,const std::string &FileGroupName,Manager::GlobalVariables::ResourcesGroupDirectory type=Manager::GlobalVariables::ResourcesGroupDirectory::Entitiys);

   void JsonImGuiUpdate();


   /// <summary>
   /// 追加
   /// </summary>
   template <typename T> void SetValue(std::string itemName, T value) { return globalVariables_->AddItem(*p_name_, itemName, value); }

   /// <summary>
   /// 入手
   /// </summary>
   template <typename T> T GetValue(std::string itemName) { return globalVariables_->GetValue<T>(*p_name_, itemName); }

   const std::string *GetJsonName() { return p_name_; }

 private:
   Manager::GlobalVariables *globalVariables_ = nullptr;

   const std::string *p_name_ = nullptr;
};

} // namespace Component
} // namespace CLEYERA
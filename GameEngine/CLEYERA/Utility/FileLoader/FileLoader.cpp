#include "FileLoader.h"

std::stringstream CLEYERA::FileLoader::CSVLoadFile(const std::string filepath) {

   std::ifstream file{};
   std::stringstream resultData{};
   file.open(filepath);
   assert(file.is_open());
   resultData << file.rdbuf();
   file.close();
   return resultData;
}

std::ifstream CLEYERA::FileLoader::JsonLoadFile(const std::string filePath) {

   std::ifstream file;
   file.open(filePath);

   if (file.fail()) {
      // ファイル開けない
      assert(0);
   }

   return file;
}

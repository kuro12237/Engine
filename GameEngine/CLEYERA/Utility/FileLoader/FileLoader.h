#pragma once
#include"pch/Pch.h"


namespace CLEYERA {

namespace FileLoader {

std::stringstream CSVLoadFile(const std::string filepath);

std::ifstream JsonLoadFile(const std::string filePath);

} // namespace FileLoader

} // namespace CLEYERA
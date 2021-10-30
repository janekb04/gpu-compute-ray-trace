#ifndef UTILITY_H
#define UTILITY_H

#include "log.h"
#include <filesystem>
#include <fstream>
#include <string>

std::string read_file(const std::filesystem::path &file_path) {
  std::ifstream file{file_path, std::ios::in | std::ios::binary};
  if (file) {
    std::string contents;
    const size_t file_size = std::filesystem::file_size(file_path);
    contents.resize(file_size);
    file.read(contents.data(), file_size);
    return contents;
  }
  LOG_ERROR("Could not open file ", file_path.string());
}

#endif
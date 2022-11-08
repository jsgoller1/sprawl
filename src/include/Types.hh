#pragma once

#include <string>

typedef std::string FilePath;
typedef std::string EntityName;

struct NotImplementedException : std::exception {
  const char* what() const noexcept override { return "Not implemented yet!\n"; }
};

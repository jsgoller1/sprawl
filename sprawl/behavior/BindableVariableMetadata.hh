#pragma once

#include <string>
#include <typeindex>

typedef struct BindableVariableMetadata {
  void* varPtr;               // Pointer to the variable
  std::type_index typeIndex;  // Type information
  std::string configKey;      // Key in the configuration file

  BindableVariableMetadata(void* ptr, const std::type_index type, const std::string key)
      : varPtr(ptr), typeIndex(type), configKey(key) {}
} BindableVariableMetadata;

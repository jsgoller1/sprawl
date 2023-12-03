#pragma once

#include <string>

#include "json/json.hpp"

class BehaviorComponentConfig {
  /*
   * This is a "dependency inversion principle" class that exists so that BehaviorComponent knows
   * nothing about the json library we are using.
   */

 public:
  BehaviorComponentConfig(const nlohmann::json& json) : jsonConfig(json) {}

  // Methods to get values by key
  // These methods can be expanded or templated to handle different types
  bool hasKey(const std::string& key) const { return jsonConfig.contains(key); }

  int getInt(const std::string& key) const {
    return jsonConfig.value(key, 0);  // Default value as 0
  }

  double getDouble(const std::string& key) const {
    return jsonConfig.value(key, double(0.0f));  // Default value as 0.0
  }

  std::string getString(const std::string& key) const {
    return jsonConfig.value(key, "");  // Default value as empty string
  }

 private:
  nlohmann::json jsonConfig;
};

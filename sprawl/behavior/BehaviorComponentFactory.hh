#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

// fwd decl
class IBehaviorComponent;

class BehaviorComponentFactory {
  /*
   * WARNING. DO NOT CALL Register() DIRECTLY. USE THE MACRO IN BehaviorComponent.hh INSTEAD.
   *
   * Direct use of Register() can cause undefined behavior, and crash your game during loading. (note to self: this is
   * because someone could map "OrcBehaviorComponent" to "SpellCasterComponent") and wind up loading the wrong component
   * during WAD loading.
   */
 public:
  template <typename T>
  static bool Register(const std::string typeName) {
    auto& factory = factories();
    factory[typeName] = []() -> std::shared_ptr<T> { return std::make_shared<T>(); };
    return true;
  }

  static std::shared_ptr<IBehaviorComponent> CreateComponent(const std::string typeName) {
    auto& factory = factories();
    auto it = factory.find(typeName);
    return it != factory.end() ? it->second() : nullptr;
  }

 private:
  static std::unordered_map<std::string, std::function<std::shared_ptr<IBehaviorComponent>()>>& factories();
};

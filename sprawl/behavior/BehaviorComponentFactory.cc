#include "BehaviorComponentFactory.hh"

std::unordered_map<std::string, std::function<std::shared_ptr<IBehaviorComponent>()>>&
BehaviorComponentFactory::factories() {
  static std::unordered_map<std::string, std::function<std::shared_ptr<IBehaviorComponent>()>> instance;
  return instance;
}

#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Component.hh"
#include "Entity.hh"
#include "Types.hh"

// forward decl
class ActorManager;

class Actor final : public Entity {
  /*
   * Actors are game objects, and are basically just named containers of components. Actors may only
   * be created or destroyed by ActorManager, which is responsible for their lifecycle. They are specialized via
   * composition of components, never by inheritance. At present, the set of components owned by an Actor is static
   * throughout its lifecycle.
   */

 public:
  std::string toString() const override;

  bool isEnabled() const;
  void setEnabled(const bool setting);

  EntityName getName() const;
  void setName(const EntityName name);

  void addComponent(const std::string componentTypeName, const std::shared_ptr<Component> component);
  void removeComponent(const UUID uuid);
  void removeComponent(const std::shared_ptr<Component> component);

  template <typename T>
  std::shared_ptr<T> getComponent() {
    for (auto& component_pair : components) {
      std::shared_ptr<T> cast_component = std::dynamic_pointer_cast<T, Component>(component_pair.second);
      if (cast_component) {
        return cast_component;
      }
    }
    return nullptr;
  }

  template <typename T>
  std::shared_ptr<std::vector<std::shared_ptr<T>>> getComponents() {
    std::shared_ptr<std::vector<std::shared_ptr<T>>> returned_components =
        std::make_shared<std::vector<std::shared_ptr<T>>>();
    for (auto& component_pair : this->components) {
      std::shared_ptr<T> cast_component = std::dynamic_pointer_cast<T, Component>(component_pair.second);
      if (cast_component) {
        returned_components->push_back(cast_component);
      }
    }
    return returned_components;
  }

  ~Actor() override = default;

 private:
  friend ActorManager;
  Actor(const EntityName name);

  bool enabled;

  EntityName name = "";
  std::unordered_map<UUID, std::shared_ptr<Component>> components = {};
};

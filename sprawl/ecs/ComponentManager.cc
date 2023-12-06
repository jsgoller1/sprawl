#include "ComponentManager.hh"

#include "Actor.hh"

ComponentManager::ComponentManager() = default;
ComponentManager::~ComponentManager() = default;

void ComponentManager::manage(const std::shared_ptr<Actor> actor) { this->managedActors[actor->getUUID()] = actor; }
void ComponentManager::unmanage(const std::shared_ptr<Actor> actor) {
  UUID uuid = actor->getUUID();
  if (this->managedActors.find(uuid) != this->managedActors.end()) {
    this->managedActors.erase(uuid);
  }
}
std::shared_ptr<Actor> ComponentManager::getActor(const UUID& uuid) const {
  if (this->managedActors.find(uuid) != this->managedActors.end()) {
    return this->managedActors.at(uuid);
  }
  return nullptr;
}

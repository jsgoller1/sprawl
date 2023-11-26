#include "ComponentManager.hh"

ComponentManager::ComponentManager() = default;
ComponentManager::~ComponentManager() = default;

void ComponentManager::manage(const std::shared_ptr<Actor> actor) { this->managedActors.insert(actor); }
void ComponentManager::unmanage(const std::shared_ptr<Actor> actor) { this->managedActors.erase(actor); }

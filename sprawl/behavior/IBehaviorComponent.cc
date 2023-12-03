#include "IBehaviorComponent.hh"

#include "Actor.hh"
#include "BehaviorManager.hh"

IBehaviorComponent::~IBehaviorComponent() { BehaviorManager::instance().unmanage(this->getOwner()); }

std::string IBehaviorComponent::toString() const {
  return fmt::format("IBehaviorComponent({})", this->getOwner()->toString());
}

void IBehaviorComponent::managerRegister() { BehaviorManager::instance().manage(this->getOwner()); }
void IBehaviorComponent::managerUnregister() { BehaviorManager::instance().unmanage(this->getOwner()); }

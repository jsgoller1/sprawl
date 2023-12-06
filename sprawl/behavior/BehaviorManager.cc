#include "BehaviorManager.hh"

#include "Actor.hh"
#include "IBehaviorComponent.hh"

BehaviorManager::BehaviorManager() { this->eventBus = std::make_unique<EventBus>(this->managedActors); };

void BehaviorManager::gameLoopUpdate(time_ms duration) { (void)duration; }

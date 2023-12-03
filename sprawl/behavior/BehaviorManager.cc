#include "BehaviorManager.hh"

#include "Actor.hh"
#include "IBehaviorComponent.hh"

BehaviorManager::BehaviorManager() = default;

void BehaviorManager::gameLoopUpdate(time_ms duration) {
  (void)duration;
  for (auto actor : managedActors) {
    for (auto component : *(actor->getComponents<IBehaviorComponent>())) {
      component->onLoop();
    }
  }
}

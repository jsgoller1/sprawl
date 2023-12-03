#include "BehaviorManager.hh"

#include "Actor.hh"
#include "IBehaviorComponent.hh"

BehaviorManager::BehaviorManager() = default;

void BehaviorManager::gameLoopUpdate(time_ms duration) {
  (void)duration;
  for (auto actor : managedActors) {
    std::shared_ptr<std::vector<std::shared_ptr<IBehaviorComponent>>> behaviorComponents =
        actor->getComponents<IBehaviorComponent>();
    for (auto component : *behaviorComponents) {
      component->onLoop();
    }
  }
}

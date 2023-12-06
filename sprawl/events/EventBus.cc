#include "EventBus.hh"

#include <memory>
#include <unordered_set>

#include "Actor.hh"
#include "EventMessage.hh"
#include "IBehaviorComponent.hh"

EventBus::EventBus(std::unordered_set<std::shared_ptr<Actor>>& subscribedActors) : subscribedActors(subscribedActors) {}

void EventBus::publish(const EventMessage& message) {
  auto it = this->subscribedActors.find(message.receiverId);
  if (it != this->subscribedActors.end()) {
    for (auto& component : *((*it)->getComponents<IBehaviorComponent>())) {
      component->receiveEvent(message);
    }
  }
}

void EventBus::broadcast(const EventMessage& message) {
  for (auto actor : this->subscribedActors) {
    for (auto& component : *(actor->getComponents<IBehaviorComponent>())) {
      component->receiveEvent(message);
    }
  }
}

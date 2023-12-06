#include "EventBus.hh"

#include <memory>
#include <unordered_set>

#include "Actor.hh"
#include "EventMessage.hh"
#include "IBehaviorComponent.hh"

EventBus::EventBus(std::unordered_map<UUID, std::shared_ptr<Actor>>& subscribedActors)
    : subscribedActors(subscribedActors) {}

void EventBus::sendMessage(const EventMessage& message) {
  message.receiverId == "" ? this->broadcast(message) : this->sendTo(message);
}

void EventBus::sendTo(const EventMessage& message) {
  auto component_it = this->subscribedActors.find(message.receiverId);
  if (component_it != this->subscribedActors.end()) {
    std::shared_ptr<Actor> actor = component_it->second;
    for (auto& component : *(actor->getComponents<IBehaviorComponent>())) {
      component->receiveEvent(message);
    }
  }
}

void EventBus::broadcast(const EventMessage& message) {
  for (auto& pair : this->subscribedActors) {
    std::shared_ptr<Actor> actor = pair.second;
    std::shared_ptr<std::vector<std::shared_ptr<IBehaviorComponent>>> components =
        actor->getComponents<IBehaviorComponent>();
    for (auto& component : *(components)) {
      component->receiveEvent(message);
    }
  }
}

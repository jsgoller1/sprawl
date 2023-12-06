#include "EventBusPublisher.hh"

#include "BehaviorManager.hh"
#include "EventBus.hh"

EventBusPublisher::EventBusPublisher() : eventBus(BehaviorManager::instance().eventBus) {}

void EventBusPublisher::publish(const EventMessage& message) const { this->eventBus->publish(message); }
void EventBusPublisher::broadcast(const EventMessage& message) const { this->eventBus->broadcast(message); }

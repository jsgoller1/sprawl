#include "EventBusPublisher.hh"

#include "BehaviorManager.hh"
#include "EventBus.hh"

EventBusPublisher::EventBusPublisher() : eventBus(BehaviorManager::instance().eventBus) {}

void EventBusPublisher::sendMessage(const EventMessage& message) const { this->eventBus->sendMessage(message); }

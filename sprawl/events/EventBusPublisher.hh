#pragma once

#include <memory>

#include "Singleton.hh"

class EventMessage;
class EventBus;

class EventBusPublisher : public Singleton<EventBusPublisher> {
  /*
   * Proxy class for interacting with Sprawl's event bus.
   */

 public:
  void publish(const EventMessage& message) const;
  void broadcast(const EventMessage& message) const;

 private:
  EventBusPublisher();
  EventBusPublisher(const EventBusPublisher&) = delete;
  EventBusPublisher& operator=(const EventBusPublisher&) = delete;

  std::shared_ptr<EventBus> eventBus;
};

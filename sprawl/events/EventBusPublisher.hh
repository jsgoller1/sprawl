#pragma once

#include <memory>

#include "Singleton.hh"

// fwd decls
struct EventMessage;
class EventBus;

class EventBusPublisher : public Singleton<EventBusPublisher> {
  /*
   * Proxy class for interacting with Sprawl's event bus.
   */

 public:
  void sendMessage(const EventMessage& message) const;

 private:
  friend class Singleton<EventBusPublisher>;
  EventBusPublisher();
  EventBusPublisher(const EventBusPublisher&) = delete;
  EventBusPublisher& operator=(const EventBusPublisher&) = delete;

  std::shared_ptr<EventBus> eventBus;
};

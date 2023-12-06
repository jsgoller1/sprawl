#pragma once

#include <memory>
#include <unordered_set>

// fwd decls
class Actor;
class EventBusPublisher;
class EventMessage;

class EventBus {
  EventBus(std::unordered_set<std::shared_ptr<Actor>>& subscribedActors);

 private:
  friend EventBusPublisher;
  void publish(const EventMessage& message);
  void broadcast(const EventMessage& message);

  std::unordered_set<std::shared_ptr<Actor>>& subscribedActors;
};

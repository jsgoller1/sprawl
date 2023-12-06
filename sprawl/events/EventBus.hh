#pragma once

#include <memory>
#include <unordered_map>

#include "Types.hh"

// fwd decls
class Actor;
class EventBusPublisher;
struct EventMessage;

class EventBus {
 public:
  EventBus(std::unordered_map<UUID, std::shared_ptr<Actor>>& subscribedActors);
  void sendMessage(const EventMessage& message);

 private:
  void sendTo(const EventMessage& message);
  void broadcast(const EventMessage& message);

  std::unordered_map<UUID, std::shared_ptr<Actor>>& subscribedActors;
};

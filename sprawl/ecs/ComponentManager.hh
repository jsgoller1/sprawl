#pragma once

#include <memory>
#include <unordered_map>

#include "Time.hh"
#include "Types.hh"

// forward decls
class Actor;

class ComponentManager {
 public:
  virtual void gameLoopUpdate(const time_ms duration) = 0;

  void manage(const std::shared_ptr<Actor> actor);
  void unmanage(const std::shared_ptr<Actor> actor);

  std::shared_ptr<Actor> getActor(const UUID& uuid) const;

 protected:
  ComponentManager();
  virtual ~ComponentManager();

  std::unordered_map<UUID, std::shared_ptr<Actor>> managedActors = {};
};

#pragma once

#include <memory>
#include <unordered_set>

#include "Time.hh"

// forward decls
class Actor;

class ComponentManager {
 public:
  virtual void gameLoopUpdate(const time_ms duration) = 0;

  void manage(const std::shared_ptr<Actor> actor);
  void unmanage(const std::shared_ptr<Actor> actor);

 protected:
  ComponentManager();
  virtual ~ComponentManager();

  std::unordered_set<std::shared_ptr<Actor>> managedActors = {};
};

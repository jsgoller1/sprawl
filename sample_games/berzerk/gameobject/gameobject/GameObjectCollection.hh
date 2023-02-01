#pragma once

#include <memory>

#include "GameObject.hh"

class GameObjectCollection {
 public:
  virtual ~GameObjectCollection();
  void collisionTestAndResolve(GameObject* source);
  void collisionTestAndResolve(GameObjectCollection* sources);
  void draw();

  virtual GameObject* get(const size_t index) = 0;
  virtual size_t size() = 0;
};

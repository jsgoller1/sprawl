#pragma once

#include "DrawingComponent.hh"
#include "GameAction.hh"
#include "Types.hh"
#include "Zone.hh"

class World {
  // Keeps track of the interactive game world state, e.g. which
  // Characters, Zones, and GameObjects exist in the world. World knows if an
  // GameObject should be drawn, but not how to draw it (Screen knows how).
  // NOTE: World implements an MVC Model
  // NOTE: Menus, UI, dialogue boxes, etc should not be part of the world

 public:
  World(const std::shared_ptr<Zone> currentZone);

  // Forward to Zone
  void gameLoopUpdate(const GameAction& action, const time_ms duration);
  std::shared_ptr<std::vector<std::shared_ptr<DrawingComponent>>> getDrawables() const;
  // TODO: serialize(); // needed for saving game and level editor

 private:
  std::shared_ptr<Zone> currentZone;
};
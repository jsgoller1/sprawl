#pragma once

#include "GameAction.hh"
#include "Memory.hh"
#include "Types.hh"
#include "Zone.hh"

class World {
  // Keeps track of the interactive game world state, e.g. which
  // Characters, Zones, and GameObjects exist in the world. World knows if an
  // GameObject should be drawn, but not how to draw it (Screen knows how).

  // TODO: Menus, UI, dialogue boxes, etc should not be part of the world

  // World implements an MVC Model

 public:
  World();
  World(const FilePathSPtr wadDirSPtr);
  void update(const GameAction& action);
  DrawingCompSPtrCollectionSPtr getDrawables();

 private:
  ZoneSPtr currentZone;
  ZoneSPtrCollection zones;
  void draw() {
    // Collects whatever GameObjects should be drawn
    // and gives them to the screen for drawing
  }
};

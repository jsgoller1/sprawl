#pragma once

#include "GameAction.hh"
#include "Memory.hh"
#include "Types.hh"
#include "Zone.hh"

class World {
  // Keeps track of the interactive game world state, e.g. which
  // Characters, Zones, and GameObjects exist in the world. World knows if an
  // GameObject should be drawn, but not how to draw it (Screen knows how).
  // NOTE: World implements an MVC Model
  // NOTE: Menus, UI, dialogue boxes, etc should not be part of the world

 public:
  World();
  World(const FilePathSPtr wadDirSPtr);
  void update(const GameAction& action);
  DrawingCompSPtrCollectionSPtr getDrawables();
  // TODO: serialize(); // needed for saving game and level editor

 private:
  ZoneSPtr currentZone;
  ZoneSPtrCollection zones;
  void draw() {
    // Collects whatever GameObjects should be drawn
    // and gives them to the screen for drawing
  }
};

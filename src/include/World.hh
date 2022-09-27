#pragma once

#include "DrawingComp.hh"
#include "GameAction.hh"
#include "Memory.hh"
#include "Types.hh"
#include "WADLoader.hh"
#include "Zone.hh"

class World {
  // Keeps track of the interactive game world state, e.g. which
  // Characters, Zones, and GameObjects exist in the world. World knows if an
  // GameObject should be drawn, but not how to draw it (Screen knows how).
  // NOTE: World implements an MVC Model
  // NOTE: Menus, UI, dialogue boxes, etc should not be part of the world

 public:
  World()
      : World(shared_ptr<FilePath>(new FilePath("./assets/wads/mvp.json"))){};
  World(const shared_ptr<FilePath> wadPath);
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

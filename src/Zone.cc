#include "Zone.hh"

#include "Character.hh"
#include "GameAction.hh"
#include "Platform.hh"
#include "Types.hh"

Zone::Zone() {}

void Zone::load(const FilePathPS zoneWADDirPS) {}

void Zone::loadHardcoded() {
  // We'll hardcode the zone state initially. Eventually, we'll want to load
  // textures, positions, music, etc from WAD files we can design as data (and
  // perhaps emit with a level design tool).
  this->gameObjects =
      shared_ptr<GameObjectPSCollection>(new GameObjectPSCollection());

  CharacterPS player = CharacterPS(new Character("player"));
  this->gameObjects->push_back(player);
  PlatformPS floor = PlatformPS(new Platform);
  this->gameObjects->push_back(floor);
}

void Zone::update(const GameAction& action) {}

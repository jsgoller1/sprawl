#include "Zone.hh"

#include "Character.hh"
#include "GameAction.hh"
#include "Platform.hh"
#include "Texture.hh"
#include "Types.hh"

Zone::Zone() {}

void Zone::load(const FilePathSPtr zoneWADDirSPtr) {}

void Zone::loadHardcoded() {
  // We'll hardcode the zone state initially. Eventually, we'll want to load
  // textures, positions, music, etc from WAD files we can design as data (and
  // perhaps emit with a level design tool).
  this->setBackground(
      FilePathSPtr(new FilePath("./assets/world-background.bmp")));
  this->gameObjects =
      shared_ptr<GameObjectSPtrCollection>(new GameObjectSPtrCollection());

  CharacterSPtr player = CharacterSPtr(new Character("player"));
  this->gameObjects->push_back(player);
  PlatformSPtr floor = PlatformSPtr(new Platform);
  this->gameObjects->push_back(floor);
}

void Zone::setBackground(const FilePathSPtr backgroundPath) {
  this->background = TextureSPtr(new Texture(backgroundPath));
}

void Zone::update(const GameAction& action) {}

#include "Zone.hh"

#include "Background.hh"
#include "Character.hh"
#include "GameAction.hh"
#include "Platform.hh"
#include "Texture.hh"
#include "Types.hh"

// TODO: Remove this; this is just for hardcoding the screen coordinates for
// loadHardcoded(); Zone should NOT know about Screen.
#include "Screen.hh"

Zone::Zone() {}

void Zone::load(const FilePathSPtr zoneWADDirSPtr) {}

void Zone::loadHardcoded() {
  // We'll hardcode the zone state initially. Eventually, we'll want to load
  // textures, positions, music, etc from WAD files we can design as data (and
  // perhaps emit with a level design tool).
  BackgroundSPtr background = BackgroundSPtr(new Background(
      FilePathSPtr(new FilePath("./assets/world-background.bmp")), nullptr,
      SCREEN_X_CENTER, SCREEN_Y_CENTER));

  this->background = background;
  this->gameObjects =
      shared_ptr<GameObjectSPtrCollection>(new GameObjectSPtrCollection());

  CharacterSPtr player = CharacterSPtr(new Character("player"));
  this->gameObjects->push_back(player);
  PlatformSPtr floor = PlatformSPtr(new Platform);
  this->gameObjects->push_back(floor);
}

void Zone::update(const GameAction& action) {}

DrawingCompSPtrCollectionSPtr Zone::getDrawables() {
  DrawingCompSPtrCollectionSPtr drawables =
      DrawingCompSPtrCollectionSPtr(new vector<DrawingCompSPtr>());
  for (GameObjectSPtr objSPtr : *(this->gameObjects)) {
    DrawingCompSPtr comp = objSPtr->getDrawingComp();
    if (comp != nullptr) {
      drawables->push_back(comp);
    }
  }
  drawables->push_back(this->background->getDrawingCompSPtr());
  return drawables;
}

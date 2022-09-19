#include "Zone.hh"

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

  CharacterSPtr player = CharacterSPtr(
      new Character(CharacterNameSPtr(new CharacterName("player")),
                    FilePathSPtr(new FilePath("./assets/player.bmp")),
                    PointSPtr(new Point{.x = 16, .y = 16})));

  // TODO: This is ugly; we should just implement a private
  // Zone::getGameObjects()
  this->player = player;
}

void Zone::update(const GameAction& action) {}

DrawingCompSPtrCollectionSPtr Zone::getDrawables() {
  DrawingCompSPtrCollectionSPtr drawables =
      DrawingCompSPtrCollectionSPtr(new vector<DrawingCompSPtr>());
  for (GameObjectSPtr objSPtr : *(this->gameObjects)) {
    DrawingCompSPtr comp = objSPtr->getDrawingCompSPtr();
    if (comp != nullptr) {
      drawables->push_back(comp);
    }
  }

  drawables->push_back(this->player->getDrawingCompSPtr());
  drawables->push_back(this->background->getDrawingCompSPtr());
  return drawables;
}

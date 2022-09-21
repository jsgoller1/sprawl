#include "Zone.hh"

// TODO: Remove this; this is just for hardcoding the screen coordinates for
// loadHardcoded(); Zone should NOT know about Screen.
#include "Screen.hh"

Zone::Zone() { this->physicsMgr = shared_ptr<PhysicsMgr>(new PhysicsMgr()); }

void Zone::load(const FilePathSPtr zoneWADDirSPtr) {}

void Zone::loadHardcoded() {
  // We'll hardcode the zone state initially. Eventually, we'll want to load
  // textures, positions, music, etc from WAD files we can design as data (and
  // perhaps emit with a level design tool).
  // TODO: This is ugly; we should just implement a private
  // Zone::getGameObjects()
  this->gameObjects =
      shared_ptr<GameObjectSPtrCollection>(new GameObjectSPtrCollection());

  // Set up background
  BackgroundSPtr background = BackgroundSPtr(new Background(
      FilePathSPtr(new FilePath("./assets/world-background.bmp")), nullptr,
      SCREEN_X_CENTER, SCREEN_Y_CENTER));
  this->background = background;

  // Set up player character
  CharacterSPtr player = CharacterSPtr(
      new Character(PointSPtr(new Point{.x = 16, .y = 16}),
                    GameObjectNameSPtr(new GameObjectName("player")), nullptr,
                    FilePathSPtr(new FilePath("./assets/player.bmp"))));
  this->player = player;
  player->inferBoundingBoxFromTexture();

  // Add a single platform
  // Center should be at 960, 540
  /* Clockwise from top-left, the four corners appear at (approx):
    Top left:(811, 393)
    Top right: (1108, 394)
    Bottom right: (1111, 685)
    Bottom left: (815, 689)
  */

  PlatformSPtr platform = PlatformSPtr(new Platform(
      PointSPtr(new Point{.x = SCREEN_X_CENTER, .y = SCREEN_Y_CENTER}),
      GameObjectNameSPtr(new GameObjectName("player")), nullptr,
      FilePathSPtr(new FilePath("./assets/wall-indestructible.bmp"))));
  platform->inferBoundingBoxFromTexture();
  this->gameObjects->push_back(platform);

  this->physicsMgr->manageComponent(platform->getPhysicsComponent());
  this->physicsMgr->manageComponent(player->getPhysicsComponent());
}

void Zone::update(const GameAction& action) {
  this->handleInput(action);
  this->physicsMgr->applyGravity();
}

void Zone::handleInput(const GameAction& action) {
  switch (action) {
    case IDLE:
      break;
    case MOVE_DOWN:
    case MOVE_UP:
    case MOVE_LEFT:
    case MOVE_RIGHT:
      log(string("Got move action: " + to_string(action)));
      this->player->move(action);
      break;
    case SHOOT_DOWN:
    case SHOOT_UP:
    case SHOOT_LEFT:
    case SHOOT_RIGHT:
      log(string("Got shoot action: " + to_string(action)));
      this->player->shoot(action);
      break;
    default:
      log(string("Unknown action: " + to_string(action)));
  }
}

DrawingCompSPtrCollectionSPtr Zone::getDrawables() {
  DrawingCompSPtrCollectionSPtr drawables =
      DrawingCompSPtrCollectionSPtr(new vector<DrawingCompSPtr>());

  // Background should be drawn first to ensure everything else gets
  // drawn over it.
  drawables->push_back(this->background->getDrawingCompSPtr());
  drawables->push_back(this->player->getDrawingComponent());
  for (GameObjectSPtr objSPtr : *(this->gameObjects)) {
    DrawingCompSPtr comp = objSPtr->getDrawingComponent();
    if (comp != nullptr) {
      drawables->push_back(comp);
    }
  }

  return drawables;
}

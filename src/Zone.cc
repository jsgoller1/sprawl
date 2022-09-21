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
      new Character(PointSPtr(new Point{.x = 400, .y = 734}),
                    GameObjectNameSPtr(new GameObjectName("player")), nullptr,
                    FilePathSPtr(new FilePath("./assets/player.bmp"))));
  this->player = player;
  player->inferBoundingBoxFromTexture();
  this->physicsMgr->manageComponent(player->getPhysicsComponent());

  // Set up enemy character
  CharacterSPtr enemy = CharacterSPtr(
      new Character(PointSPtr(new Point{.x = 650, .y = 734}),
                    GameObjectNameSPtr(new GameObjectName("enemy")), nullptr,
                    FilePathSPtr(new FilePath("./assets/enemy.bmp"))));
  enemy->inferBoundingBoxFromTexture();
  this->gameObjects->push_back(enemy);
  this->physicsMgr->manageComponent(enemy->getPhysicsComponent());

  for (int x = 0; x < 1920 + (300 * 2); x += 300) {
    // Add a single platform
    PlatformSPtr platform = PlatformSPtr(new Platform(
        PointSPtr(
            new Point{.x = (PositionUnit)x, .y = SCREEN_Y_CENTER * 2 - 20}),
        nullptr, nullptr,
        FilePathSPtr(new FilePath("./assets/wall-indestructible.bmp"))));
    platform->inferBoundingBoxFromTexture();
    this->gameObjects->push_back(platform);
    this->physicsMgr->manageComponent(platform->getPhysicsComponent());
  }
}

void Zone::update(const GameAction& action) {
  this->handleInput(action);
  this->physicsMgr->applyGravity();
  this->physicsMgr->applyVelocity();
}

void Zone::handleInput(const GameAction& action) {
  switch (action) {
    case IDLE:
      break;
    case MOVE_DOWN:
    case MOVE_UP:
    case STOP_MOVE_LEFT:
    case STOP_MOVE_RIGHT:
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

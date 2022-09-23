#include "Zone.hh"

// TODO: Remove this; this is just for hardcoding the screen coordinates for
// loadHardcoded(); Zone should NOT know about Screen.
#include "Screen.hh"

Zone::Zone() {
  this->physicsMgr = shared_ptr<PhysicsMgr>(new PhysicsMgr());
  this->gameObjects =
      shared_ptr<GameObjectSPtrCollection>(new GameObjectSPtrCollection());
<<<<<<< HEAD
=======

  // Set up background
  BackgroundSPtr background = BackgroundSPtr(new Background(
      FilePathSPtr(new FilePath("./assets/world-background.bmp")), nullptr,
      SCREEN_X_CENTER, SCREEN_Y_CENTER));
  this->background = background;

  // Set up player character
  CharacterSPtr player = CharacterSPtr(
      new Character(shared_ptr<Vect2D>(new Vect2D{.x = 400, .y = 734}),
                    GameObjectNameSPtr(new GameObjectName("player")), nullptr,
                    FilePathSPtr(new FilePath("./assets/player.bmp"))));
  this->player = player;
  player->inferBoundingBoxFromTexture();
  this->physicsMgr->manageComponent(player->getPhysicsComponent());

  // Set up enemy character
  CharacterSPtr enemy = CharacterSPtr(
      new Character(shared_ptr<Vect2D>(new Vect2D{.x = 1450, .y = 734}),
                    GameObjectNameSPtr(new GameObjectName("enemy")), nullptr,
                    FilePathSPtr(new FilePath("./assets/enemy.bmp"))));
  enemy->inferBoundingBoxFromTexture();
  this->gameObjects->push_back(enemy);
  this->physicsMgr->manageComponent(enemy->getPhysicsComponent());

  for (int x = 0; x < 1920 + (300 * 2); x += 300) {
    // Add a single platform
    PlatformSPtr platform = PlatformSPtr(new Platform(
        shared_ptr<Vect2D>(
            new Vect2D{.x = (PositionUnit)x, .y = SCREEN_Y_CENTER * 2 - 20}),
        nullptr, nullptr,
        FilePathSPtr(new FilePath("./assets/wall-indestructible.bmp"))));
    platform->inferBoundingBoxFromTexture();
    this->gameObjects->push_back(platform);
    this->physicsMgr->manageComponent(platform->getPhysicsComponent());
  }

  PlatformSPtr tallWall = PlatformSPtr(new Platform(
      shared_ptr<Vect2D>(new Vect2D{.x = (PositionUnit)1200,
                                        .y = (SCREEN_Y_CENTER * 2 - 20) - 250}),
      nullptr, nullptr, FilePathSPtr(new FilePath("./assets/wall-tall.bmp"))));
  tallWall->inferBoundingBoxFromTexture();
  this->gameObjects->push_back(tallWall);
  this->physicsMgr->manageComponent(tallWall->getPhysicsComponent());
>>>>>>> 63a94b0 (ready to start implementation)
}

void Zone::load(const FilePathSPtr zoneWADDirSPtr) {}

void Zone::update(const GameAction& action) {
  this->handleInput(action);
  this->physicsMgr->applyVelocityAll();
}

void Zone::handleInput(const GameAction& action) {
  switch (action) {
    case IDLE:
      break;
    case MOVE_DOWN:
    case STOP_MOVE_LEFT:
    case STOP_MOVE_RIGHT:
    case MOVE_LEFT:
    case MOVE_RIGHT:
      log(string("Got move action: " + to_string(action)));
      this->player->move(action);
      break;
    case MOVE_UP:
      log(string("Got move action: " + to_string(action)));
      this->player->jump();
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

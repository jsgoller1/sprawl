#include "Zone.hh"

// TODO: Remove this; this is just for hardcoding the screen coordinates for
// loadHardcoded(); Zone should NOT know about Screen.
#include "Screen.hh"

Zone::Zone() {
  this->physicsMgr = shared_ptr<PhysicsManager>(new PhysicsManager());
  this->gameObjects =
      shared_ptr<GameObjectSPtrCollection>(new GameObjectSPtrCollection());
}

void Zone::load(const FilePathSPtr zoneWADDirSPtr) {}

void Zone::update(const GameAction& action, const time_ms duration) {
  this->handleInput(action);
  this->physicsMgr->updateManagedComponents(duration);
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

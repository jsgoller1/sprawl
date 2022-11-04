#include "Zone.hh"

// TODO: Remove this; this is just for hardcoding the screen coordinates for
// loadHardcoded(); Zone should NOT know about Screen.
#include "Screen.hh"

Zone::Zone() {
  this->physicsManager = shared_ptr<PhysicsManager>(new PhysicsManager());
  this->gameObjects = shared_ptr<vector<shared_ptr<GameObject>>>(new vector<shared_ptr<GameObject>>());
}

void Zone::setGravityConstant(const real gravityConstant) { this->physicsManager->setGravityConstant(gravityConstant); }

void Zone::setBackground(const shared_ptr<Background> background) { this->background = background; }

void Zone::gameLoopUpdate(const GameAction& action, const time_ms duration) {
  this->handleInput(action);
  this->physicsManager->gameLoopUpdate(duration);
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
      LOG_INFO_SYS(ZONE, string("Got move action: {0}", action));
      this->player->move(action);
      break;
    case MOVE_UP:
      LOG_INFO_SYS(ZONE, string("Got move action: {0}", action));
      this->player->jump();
      break;
    case SHOOT_DOWN:
    case SHOOT_UP:
    case SHOOT_LEFT:
    case SHOOT_RIGHT:
      LOG_INFO_SYS(ZONE, string("Got shoot action: {0}", action));
      break;
    default:
      LOG_DEBUG_SYS(ZONE, string("Got move unknown action: {0}", action));
  }
}

shared_ptr<vector<shared_ptr<DrawingComponent>>> Zone::getDrawables() const {
  shared_ptr<vector<shared_ptr<DrawingComponent>>> drawables =
      shared_ptr<vector<shared_ptr<DrawingComponent>>>(new vector<shared_ptr<DrawingComponent>>());

  // Background should be drawn first to ensure everything else gets
  // drawn over it.
  drawables->push_back(this->background->getDrawingComponent());
  drawables->push_back(this->player->getDrawingComponent());
  for (shared_ptr<GameObject> obj : *(this->gameObjects)) {
    shared_ptr<DrawingComponent> comp = obj->getDrawingComponent();
    if (comp != nullptr) {
      drawables->push_back(comp);
    }
  }

  return drawables;
}

void Zone::addPlayerCharacter(const shared_ptr<Character> playerCharacter) {
  this->player = playerCharacter;
  this->physicsManager->manage(playerCharacter->getIdentity(), playerCharacter->getPhysicsComponent(),
                               playerCharacter->getPositionComponent(), playerCharacter->getCollisionComponent());
}

void Zone::addGameObject(const shared_ptr<GameObject> gameObject) {
  this->gameObjects->push_back(gameObject);
  this->physicsManager->manage(gameObject->getIdentity(), gameObject->getPhysicsComponent(),
                               gameObject->getPositionComponent(), gameObject->getCollisionComponent());
}

#include "IntegrationWorld.hh"

void IntegrationWorld::addPlayerCharacter(const std::shared_ptr<Character> playerCharacter) {
  this->playerCharacter = playerCharacter;
  this->getPhysicsManager()->manage(playerCharacter->getIdentity(), playerCharacter->getPhysicsComponent(),
                                    playerCharacter->getPositionComponent(), playerCharacter->getCollisionComponent());
}

void IntegrationWorld::handleInput(const std::shared_ptr<GameLoopInputEvents> inputEvents) {
  /*
   * TODO: Presently, we assume that there is only one InputEvent to be handled. This
   * will later be false and we will need to iterate over inputEvents until it is empty.
   */
  if (inputEvents->empty()) {
    LOG_DEBUG_SYS(LoggingSubsystem::ZONE, "No inputs detected during this loop.");
    return;
  }
  // TODO: GameObject behaviors that occur in response to input need to be decided by game, not Sprawl.
  GameAction action = inputEvents->extract()->getGameAction();
  switch (action) {
    case IDLE:
      break;
    case MOVE_DOWN:
    case MOVE_LEFT:
    case MOVE_RIGHT:
      LOG_INFO_SYS(ZONE, std::string("Got move action: {0}", action));
      this->playerCharacter->move(action);
      break;
    case MOVE_UP:
      LOG_INFO_SYS(ZONE, std::string("Got move action: {0}", action));
      this->playerCharacter->jump();
      break;
    case SHOOT_DOWN:
    case SHOOT_UP:
    case SHOOT_LEFT:
    case SHOOT_RIGHT:
      LOG_INFO_SYS(ZONE, std::string("Got shoot action: {0}", action));
      break;
    default:
      LOG_DEBUG_SYS(ZONE, std::string("Got move unknown action: {0}", action));
  }
}

std::shared_ptr<std::vector<std::shared_ptr<DrawingComponent>>> IntegrationWorld::getDrawables() const {
  std::shared_ptr<std::vector<std::shared_ptr<DrawingComponent>>> drawables =
      std::shared_ptr<std::vector<std::shared_ptr<DrawingComponent>>>(
          new std::vector<std::shared_ptr<DrawingComponent>>());

  // Background should be drawn first to ensure everything else gets
  // drawn over it.
  drawables->push_back(this->getBackground()->getDrawingComponent());
  drawables->push_back(this->playerCharacter->getDrawingComponent());
  for (std::shared_ptr<GameObject> obj : *(this->getGameObjects())) {
    std::shared_ptr<DrawingComponent> comp = obj->getDrawingComponent();
    if (comp != nullptr) {
      drawables->push_back(comp);
    }
  }

  return drawables;
}

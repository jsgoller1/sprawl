#include "PorngWorld.hh"

#include "GameLoopInputEvents.hh"
#include "GraphicsSettings.hh"
#include "World.hh"

PorngWorld::PorngWorld(const GraphicsSettings& screenParameters) : World(screenParameters) {}

void PorngWorld::setPlayerPaddle(const std::shared_ptr<Paddle> playerPaddle) { this->_playerPaddle = playerPaddle; }
Paddle& PorngWorld::getPlayerPaddle() { return *this->_playerPaddle; }
void PorngWorld::setAIPaddle(const std::shared_ptr<Paddle> aiPaddle) { this->_aiPaddle = aiPaddle; }
Paddle& PorngWorld::getAIPaddle() { return *this->_aiPaddle; }
void PorngWorld::gameLoopUpdate(const std::shared_ptr<GameLoopInputEvents> inputEvents, const time_ms duration) {
  World::gameLoopUpdate(inputEvents, duration);
  switch (this->currentState) {
    case BETWEEN_MATCHES:
      break;
    case BETWEEN_ROUNDS:
      break;
    case ROUND_ONGOING:
      break;
    case QUITTING:
      break;
  }
}

void PorngWorld::handleInput(const std::shared_ptr<GameLoopInputEvents> inputEvents) {
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
    case MOVE_DOWN:
      LOG_INFO_SYS(ZONE, std::string("Got move action: {0}", action));
      this->_playerPaddle->move(Vect2D(0.0, -10.0));
      break;
    case MOVE_UP:
      LOG_INFO_SYS(ZONE, std::string("Got move action: {0}", action));
      this->_playerPaddle->move(Vect2D(0.0, 10.0));
      break;
    default:
      LOG_DEBUG_SYS(ZONE, std::string("Got move unknown action: {0}", action));
  }
}

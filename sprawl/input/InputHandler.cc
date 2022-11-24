#include "InputHandler.hh"

#include "SDLInputInterface.hh"

InputHandler::InputHandler() { this->_sdlInputInterface = std::unique_ptr<SDLInputInterface>(new SDLInputInterface()); }

void InputHandler::batchEmplaceInputEvents(std::shared_ptr<std::queue<std::shared_ptr<SDL_Event>>> sdlEventQueue,
                                           std::shared_ptr<GameLoopInputEvents> inputEventQueue) {
  while (!sdlEventQueue->empty()) {
    inputEventQueue->insert(InputEventFactory(*(sdlEventQueue->front())));
    sdlEventQueue->pop();
  }
}

std::shared_ptr<GameLoopInputEvents> InputHandler::getGameLoopInputEvents() {
  std::shared_ptr<GameLoopInputEvents> gameLoopEvents = std::shared_ptr<GameLoopInputEvents>(new GameLoopInputEvents());
  this->_sdlInputInterface->detectInput();
  this->batchEmplaceInputEvents(this->_sdlInputInterface->getKeydownEvents(), gameLoopEvents);
  this->batchEmplaceInputEvents(this->_sdlInputInterface->getMouseButtonDownEvents(), gameLoopEvents);
  this->batchEmplaceInputEvents(this->_sdlInputInterface->getMouseMotionEvents(), gameLoopEvents);
  gameLoopEvents->setShouldQuit(this->_sdlInputInterface->recievedQuitEvent());
  return gameLoopEvents;
}

#pragma once

#include "GameLoopInputEvents.hh"
#include "InputEvent.hh"
#include "Types.hh"

// Forward decls
class SDLInputInterface;

class InputHandler {
 public:
  InputHandler();
  std::shared_ptr<GameLoopInputEvents> getGameLoopInputEvents();

 private:
  std::unique_ptr<SDLInputInterface> _sdlInputInterface;
  void batchEmplaceInputEvents(std::shared_ptr<std::queue<std::shared_ptr<SDL_Event>>> sdlEventQueue,
                               std::shared_ptr<GameLoopInputEvents> gameLoopInputEvents);
};

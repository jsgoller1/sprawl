#pragma once

#include <SDL2/SDL.h>

#include <map>
#include <memory>
#include <queue>

#include "Logging.hh"

class SDLInputInterface {
  /*
   * SDLInputInterface's maintains several std::queue of SDL_Event that are updated each loop.  SDL appears to be
   * delegating to the keyboard and mouse drivers to determine when a key/button is being held down. On my system (and
   * apparently others), this results in odd behavior when continuously holding a key down, where the initial keystroke
   * is detected, but then a delay occurs before more events are emitted. To account for this, we determine when a key
   * is pressed and released based on waiting for an SDL_KEYDOWN or SDL_BUTTONDOWN event, and then waiting for the
   * corresponding SDL_KEYUP or SDL_BUTTONUP event.
   */

 public:
  SDLInputInterface();
  bool recievedQuitEvent() const;
  std::shared_ptr<std::queue<std::shared_ptr<SDL_Event>>> getKeydownEvents();
  std::shared_ptr<std::queue<std::shared_ptr<SDL_Event>>> getMouseButtonDownEvents();
  std::shared_ptr<std::queue<std::shared_ptr<SDL_Event>>> getMouseMotionEvents();
  void detectInput();

 private:
  /*
   * SDL implements SDL_Event as a union with a type field that must be checked at runtime, no easy OOP way to avoid
   * RTTI here if we want to compare events. Sorry, uncle bob. :'(
   */
  bool _recievedQuitEvent;

  void handler_SDL_KEYDOWN(const std::shared_ptr<SDL_Event> event);
  void handler_SDL_KEYUP(const std::shared_ptr<SDL_Event> event);
  void handler_SDL_MOUSEBUTTONDOWN(const std::shared_ptr<SDL_Event> event);
  void handler_SDL_MOUSEBUTTONUP(const std::shared_ptr<SDL_Event> event);
  void handler_SDL_MOUSEMOTION(const std::shared_ptr<SDL_Event> event);

  std::shared_ptr<std::map<SDL_Keycode, std::shared_ptr<SDL_Event>>> _pressedKeys;
  std::shared_ptr<std::map<Uint8, std::shared_ptr<SDL_Event>>> _pressedMouseButtons;
  std::shared_ptr<std::queue<std::shared_ptr<SDL_Event>>> _mouseMotionEvents;
};

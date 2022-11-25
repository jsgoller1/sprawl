#pragma once

#include "SDL2/SDL.h"

#include <memory>
#include <queue>

#include "KeyboardPressEvent.hh"
#include "MouseButtonPressEvent.hh"
#include "MouseMotionEvent.hh"

/*
 * Opaque set-like collection of input events detected during a game loop. There is no guarantee of the
 * ordering of elements, but they can be safely assumed to be unique.
 */
class GameLoopInputEvents {
 public:
  GameLoopInputEvents();
  bool getShouldQuit() const;
  void setShouldQuit(const bool shouldQuit);
  bool empty() const;
  void insert(const std::shared_ptr<InputEvent> event);
  std::shared_ptr<InputEvent> extract();

 private:
  std::unique_ptr<std::queue<std::shared_ptr<InputEvent>>> _events;
  bool _shouldQuit;
};

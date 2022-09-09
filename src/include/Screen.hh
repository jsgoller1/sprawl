#pragma once

#include <SDL2/SDL.h>

#include "Memory.hh"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Screen {
  // Screen manages actually drawing stuff on the screen; for now, it handles
  // any SDL functionality related to drawing the window and actually putting
  // things in it. All entities in the World _can_ be drawn, and Screen knows
  // how. However, only World knows _if_ an GameObject should be drawn; it then
  // communicates this to Screen.

  // Screen implements an MVC View.

  // TODO: Menu, UI, dialogue boxes, etc should always be drawn on top of items
  // from World; when the UI system is implemented, it will tell Screen what to
  // draw, but all of it will take precedence over World items.

 public:
  Screen();
  Screen(const Screen&);
  ~Screen();

  void draw();

 private:
  SDL_Window* window;
  unique_ptr<SDL_Surface> surface;
};

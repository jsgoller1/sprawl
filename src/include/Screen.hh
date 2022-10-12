#pragma once

#include "DrawingComponent.hh"
#include "Logger.hh"
#include "Memory.hh"
#include "Renderer.hh"
#include "Types.hh"

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
  Screen(const ScreenWidth width, const ScreenHeight height);
  Screen(const Screen&);
  ~Screen();

  void drawAll(
      const shared_ptr<vector<shared_ptr<DrawingComponent>>> drawables) const;
  void update() const;
  void clear() const;

 private:
  // TODO: Do we actually want to use C++ smart pointers
  // with these SDL objects? Any good reason to do so, and will
  // there be drawbacks (e.g accidental automatic garbage collection)?
  unique_ptr<SDL_Surface> surface;
  SDL_Window* window;
  shared_ptr<Renderer> renderer;
};

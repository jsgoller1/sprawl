#pragma once
#include <SDL2/SDL.h>

#include "DrawingComp.hh"
#include "Memory.hh"

class Renderer {
 public:
  void prepare(DrawingCompSPtr drawable);
  void render();
  void clear();
  Renderer(SDL_Window* window, bool useHardwareAcceleration, bool useVSync);

 private:
  SDL_Renderer* renderer;
  SDL_Texture* prepareTexture(TextureSPtr textureSPtr);
};

typedef shared_ptr<Renderer> RendererSPtr;

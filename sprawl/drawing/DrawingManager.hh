#pragma once

#include <map>
#include <memory>

#include "ComponentManager.hh"
#include "Math.hh"
#include "SDL2/SDL.h"
#include "Singleton.hh"
#include "Types.hh"

// Forward decls
class DrawingComponent;
class PositionComponent;
class Identity;
class Texture;
struct GraphicsSettings;

class DrawingManager : public ComponentManager, public Singleton<DrawingManager> {
  // DrawingManager manages actually drawing stuff on the screen; for now, it handles
  // any SDL functionality related to drawing the window and actually putting
  // things in it. All entities in the World _can_ be drawn, and DrawingManager knows
  // how. However, only World knows _if_ an GameObject should be drawn; it then
  // communicates this to DrawingManager.

  // TODO: Menu, UI, dialogue boxes, etc should always be drawn on top of items
  // from World; when the UI system is implemented, it will tell DrawingManager what to
  // draw, but all of it will take precedence over World items.

 public:
  void initialize(const GraphicsSettings& graphicsSettings);
  ~DrawingManager() override;
  void gameLoopUpdate(const time_ms duration) override;
  Vect2D toScreenCoordinates(const Vect2D& vect) const;

 private:
  friend Singleton<DrawingManager>;
  DrawingManager() = default;
  DrawingManager(const DrawingManager&) = delete;
  DrawingManager& operator=(const DrawingManager&) = delete;

  ScreenWidth _screenWidth;
  ScreenHeight _screenHeight;
  SDL_Window* _window;
  SDL_Renderer* _renderer;
  bool _useHardwareAcceleration = true;
  bool _useVSync = true;

  SDL_Texture* prepareTexture(const Texture& texture) const;
  Vect2D getDrawPoint(const PositionComponent& positionComponent) const;
  void prepare(const PositionComponent& positionComponent, const DrawingComponent& drawable) const;
  void clear() const;
};

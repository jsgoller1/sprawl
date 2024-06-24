#pragma once

#include <map>
#include <memory>

#include "ComponentManager.hh"
#include "Math.hh"
#include "SDL3/SDL.h"
#include "Singleton.hh"
#include "Types.hh"

// Forward decls
class GraphicsComponent2D;
class PositionComponent;
class Identity;
class Texture;
struct GraphicsSettings;

class GraphicsManager2D : public ComponentManager, public Singleton<GraphicsManager2D> {
  // GraphicsManager2D manages actually graphics stuff on the screen; for now, it handles
  // any SDL functionality related to graphics the window and actually putting
  // things in it. All entities in the World _can_ be drawn, and GraphicsManager2D knows
  // how. However, only World knows _if_ an GameObject should be drawn; it then
  // communicates this to GraphicsManager2D.

  // TODO: Menu, UI, dialogue boxes, etc should always be drawn on top of items
  // from World; when the UI system is implemented, it will tell GraphicsManager2D what to
  // draw, but all of it will take precedence over World items.

 public:
  void initialize(const GraphicsSettings& graphicsSettings);
  ~GraphicsManager2D() override;
  void gameLoopUpdate(const time_ms duration) override;
  Vect2D toScreenCoordinates(const Vect2D& vect) const;

 private:
  friend Singleton<GraphicsManager2D>;
  GraphicsManager2D() = default;
  GraphicsManager2D(const GraphicsManager2D&) = delete;
  GraphicsManager2D& operator=(const GraphicsManager2D&) = delete;

  ScreenWidth _screenWidth;
  ScreenHeight _screenHeight;
  SDL_Window* _window;
  SDL_Renderer* _renderer;
  bool _useHardwareAcceleration = true;
  bool _useVSync = true;

  SDL_Texture* prepareTexture(const Texture& texture) const;
  Vect2D getDrawPoint(const PositionComponent& positionComponent) const;
  void prepare(const PositionComponent& positionComponent, const GraphicsComponent2D& drawable) const;
  void clear() const;
};

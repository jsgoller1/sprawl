#pragma once

#include <map>
#include <memory>

#include "Math.hh"
#include "SDL2/SDL.h"
#include "Types.hh"

// Forward decls
class DrawingComponent;
class PositionComponent;
class Identity;
class Texture;
struct GraphicsSettings;

class DrawingManager {
  // DrawingManager manages actually drawing stuff on the screen; for now, it handles
  // any SDL functionality related to drawing the window and actually putting
  // things in it. All entities in the World _can_ be drawn, and DrawingManager knows
  // how. However, only World knows _if_ an GameObject should be drawn; it then
  // communicates this to DrawingManager.

  // TODO: Menu, UI, dialogue boxes, etc should always be drawn on top of items
  // from World; when the UI system is implemented, it will tell DrawingManager what to
  // draw, but all of it will take precedence over World items.

 public:
  DrawingManager(const GraphicsSettings& graphicsSettings);
  ~DrawingManager();
  void manage(const std::shared_ptr<Identity> identity, const std::shared_ptr<PositionComponent> positionComponent,
              const std::shared_ptr<DrawingComponent> drawingComponent);
  void unmanage(const std::shared_ptr<Identity> identity);
  void gameLoopUpdate(const time_ms duration);
  Vect2D toScreenCoordinates(const Vect2D& vect) const;

 private:
  typedef struct ManagementEntry {
    const std::shared_ptr<PositionComponent> positionComponent;
    const std::shared_ptr<DrawingComponent> drawingComponent;
    ManagementEntry(const std::shared_ptr<PositionComponent> positionComponent,
                    const std::shared_ptr<DrawingComponent> drawingComponent);
  } ManagementEntry;
  std::map<std::shared_ptr<Identity>, std::shared_ptr<ManagementEntry>> managementEntries =
      std::map<std::shared_ptr<Identity>, std::shared_ptr<ManagementEntry>>();

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

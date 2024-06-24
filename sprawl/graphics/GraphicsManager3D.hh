#pragma once

#include <vulkan/vulkan.h>

#include <map>
#include <memory>

#include "ComponentManager.hh"
#include "SDL3/SDL.h"
#include "SDL3/SDL_vulkan.h"
#include "Singleton.hh"

// Forward decls
struct GraphicsSettings;

class GraphicsManager3D : public ComponentManager, public Singleton<GraphicsManager3D> {
 public:
  void initialize(const GraphicsSettings& graphicsSettings);
  ~GraphicsManager3D() override;
  void gameLoopUpdate(const time_ms duration) override;

 private:
  friend Singleton<GraphicsManager3D>;
  GraphicsManager3D() = default;
  GraphicsManager3D(const GraphicsManager3D&) = delete;
  GraphicsManager3D& operator=(const GraphicsManager3D&) = delete;

  void createVulkanInstance();

  ScreenWidth _screenWidth;
  ScreenHeight _screenHeight;
  SDL_Window* _window;

  VkInstance _instance;
};

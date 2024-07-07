#pragma once

#include <vulkan/vulkan.h>

#include <map>
#include <memory>
#include <optional>

#include "ComponentManager.hh"
#include "SDL3/SDL.h"
#include "SDL3/SDL_vulkan.h"
#include "Singleton.hh"

// Forward decls
struct GraphicsSettings;

typedef struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  bool isComplete() { return graphicsFamily.has_value(); }
} QueueFamilyIndices;

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
  bool checkVulkanValidationLayerSupport();
  void setupDebugMessenger();
  static VKAPI_ATTR VkBool32 VKAPI_CALL vulkanDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                            VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                            void* pUserData);

  VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                        const VkAllocationCallbacks* pAllocator,
                                        VkDebugUtilsMessengerEXT* pDebugMessenger);
  void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                     const VkAllocationCallbacks* pAllocator);
  void pickPhysicalDevice();
  bool isDeviceSuitable(VkPhysicalDevice device);
  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

  ScreenWidth _screenWidth;
  ScreenHeight _screenHeight;
  SDL_Window* _window;

  VkInstance _instance;
  VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
  VkDebugUtilsMessengerEXT _debugMessenger;
};

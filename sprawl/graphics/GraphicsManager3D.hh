#pragma once

#include <vulkan/vulkan.h>

#include <map>
#include <memory>
#include <optional>
#include <vector>

#include "ComponentManager.hh"
#include "SDL3/SDL.h"
#include "SDL3/SDL_vulkan.h"
#include "Singleton.hh"

// Forward decls
struct GraphicsSettings;

typedef struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
} QueueFamilyIndices;

typedef struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
} SwapChainSupportDetails;

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
  void createLogicalDevice();
  void createSurface();
  bool checkDeviceExtensionSupport(VkPhysicalDevice device);
  SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice candidateDevice);
  VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

  ScreenWidth _screenWidth;
  ScreenHeight _screenHeight;
  SDL_Window* _window;
  VkDebugUtilsMessengerEXT _debugMessenger;

  VkInstance _instance;
  VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
  VkDevice _device;
  std::vector<const char*> _instanceExtensions = {VK_EXT_DEBUG_REPORT_EXTENSION_NAME, "VK_EXT_debug_utils"};
  std::vector<const char*> _deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

  VkQueue _graphicsQueue;
  VkQueue _presentQueue;
  VkSurfaceKHR _surface;
};

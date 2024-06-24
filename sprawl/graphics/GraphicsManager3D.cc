#include "GraphicsManager3D.hh"

#include <vector>

GraphicsManager3D::~GraphicsManager3D() {}

void GraphicsManager3D::initialize(const GraphicsSettings& graphicsSettings) {
  (void)graphicsSettings;
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    return;
  }

  this->_screenWidth = 1600;
  this->_screenHeight = 1200;

  // Init SDL, create SDL window, create SDL renderer
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOG_FATAL_SYS(SDL, "Could not init SDL; {0}", Logging::getSDLError());
    throw;
  }
  this->_window = SDL_CreateWindow("Sprawl Engine (3D)", int(this->_screenWidth), int(this->_screenHeight), 0);
  if (this->_window == nullptr) {
    LOG_FATAL_SYS(SDL, "Window could not be created! {0}", Logging::getSDLError());
    throw;
  }

  createVulkanInstance();
}

void GraphicsManager3D::createVulkanInstance() {
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Hello Triangle";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  // TODO: This is C-style and copy/pasted here from the SDL wiki to get this shit working
  // https://wiki.libsdl.org/SDL3/SDL_Vulkan_GetInstanceExtensions

  // Retrieve Vulkan instance extensions
  unsigned int extensionCount = 0;
  const char* const* instance_extensions = SDL_Vulkan_GetInstanceExtensions(&extensionCount);
  if (instance_extensions == nullptr) {
    return;
  }

  Uint32 count_extensions = extensionCount;
  const char** extensions = (const char**)SDL_malloc(count_extensions * sizeof(const char*));
  extensions[0] = VK_EXT_DEBUG_REPORT_EXTENSION_NAME;
  SDL_memcpy(&extensions[1], instance_extensions, extensionCount * sizeof(const char*));

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  createInfo.enabledExtensionCount = count_extensions;
  createInfo.ppEnabledExtensionNames = extensions;

  VkResult result = vkCreateInstance(&createInfo, nullptr, &this->_instance);
  if (result) {
    return;
  }
  SDL_free(extensions);
}

void GraphicsManager3D::gameLoopUpdate(const time_ms duration) { (void)duration; }

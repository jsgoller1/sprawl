#include "GraphicsManager3D.hh"

#include <vector>

#include "Logging.hh"

const std::vector<const char*> VALIDATION_LAYERS = {"VK_LAYER_KHRONOS_validation"};
static const char* VK_DEBUG_UTILS_EXTENSION = "VK_EXT_debug_utils";

GraphicsManager3D::~GraphicsManager3D() {
  DestroyDebugUtilsMessengerEXT(this->_instance, this->_debugMessenger, nullptr);
  vkDestroyInstance(this->_instance, nullptr);
  SDL_DestroyWindow(this->_window);
  SDL_Quit();
}

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
  setupDebugMessenger();
}

void GraphicsManager3D::gameLoopUpdate(const time_ms duration) { (void)duration; }

void GraphicsManager3D::createVulkanInstance() {
  if (!checkVulkanValidationLayerSupport()) {
    throw std::runtime_error("validation layers requested, but not available!");
  }

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
    throw std::runtime_error("failed to get extensions!");
  }

  // +1 for adding VK_EXT_debug_utils
  Uint32 count_extensions = extensionCount + 1;
  const char** extensions = (const char**)SDL_malloc((count_extensions) * sizeof(const char*));
  // TODO: This creates a memory error where we are attempting to free the static memory
  // associated with VK_DEBUG_UTILS_EXTENSION; it happens after shutdown so we don't care right now.
  extensions[0] = VK_EXT_DEBUG_REPORT_EXTENSION_NAME;
  extensions[1] = VK_DEBUG_UTILS_EXTENSION;
  SDL_memcpy(&extensions[2], instance_extensions, extensionCount * sizeof(const char*));

  LOG_DEBUG_SYS(RENDERING, "Vulkan extensions enabled:");
  for (uint32_t i = 0; i < extensionCount; ++i) {
    LOG_DEBUG_SYS(RENDERING, extensions[i]);
  }

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  createInfo.enabledExtensionCount = extensionCount;
  createInfo.ppEnabledExtensionNames = extensions;
  createInfo.enabledLayerCount = static_cast<uint32_t>(VALIDATION_LAYERS.size());
  createInfo.ppEnabledLayerNames = VALIDATION_LAYERS.data();

  // TODO: We want validation layer coverage around instance creation and destruction too
  VkResult result = vkCreateInstance(&createInfo, nullptr, &this->_instance);
  if (result) {
    throw std::runtime_error("failed to create instance!");
  }
  LOG_DEBUG_SYS(RENDERING, "Created Vulkan instance!");

  SDL_free(extensions);
}

bool GraphicsManager3D::checkVulkanValidationLayerSupport() {
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  for (const char* layerName : VALIDATION_LAYERS) {
    for (const auto& layerProperties : availableLayers) {
      if (strcmp(layerName, layerProperties.layerName) == 0) {
        LOG_DEBUG_SYS(RENDERING, "Validation layer support detected: {0}", layerProperties.layerName);
        return true;
      }
    }
  }
  return false;
}

// TODO: These flags are meaningful information and need to be converted to strings.
VKAPI_ATTR VkBool32 VKAPI_CALL GraphicsManager3D::vulkanDebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
  (void)messageSeverity;
  (void)messageType;
  (void)pUserData;

  LOG_DEBUG_SYS(RENDERING, "Vulkan validation layer message: {0}", pCallbackData->pMessage);
  return VK_FALSE;
}

void GraphicsManager3D::setupDebugMessenger() {
  VkDebugUtilsMessengerCreateInfoEXT createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  createInfo.pfnUserCallback = this->vulkanDebugCallback;
  createInfo.pUserData = nullptr;  // Optional

  if (this->CreateDebugUtilsMessengerEXT(this->_instance, &createInfo, nullptr, &this->_debugMessenger) != VK_SUCCESS) {
    throw std::runtime_error("failed to set up debug messenger!");
  }
}

// NOTE: This is a helper function used to help create the debug messenger. vkCreateDebugUtilsMessengerEXT()
// is an extension function not loaded by default so we need a function to confirm it exists and get its address
// before trying to call it.
VkResult GraphicsManager3D::CreateDebugUtilsMessengerEXT(VkInstance instance,
                                                         const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                                         const VkAllocationCallbacks* pAllocator,
                                                         VkDebugUtilsMessengerEXT* pDebugMessenger) {
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
  if (func != nullptr) {
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  } else {
    LOG_FATAL_SYS(RENDERING, "Vulkan: Could not create debug messenger function!");
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}

void GraphicsManager3D::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                                      const VkAllocationCallbacks* pAllocator) {
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr) {
    func(instance, debugMessenger, pAllocator);
  }
}

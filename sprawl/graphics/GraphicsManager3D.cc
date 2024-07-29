#include "GraphicsManager3D.hh"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <limits>
#include <set>

#include "Logging.hh"

const std::vector<const char*> VALIDATION_LAYERS = {"VK_LAYER_KHRONOS_validation"};

GraphicsManager3D::~GraphicsManager3D() {
  LOG_DEBUG_SYS(RENDERING, "Destroying command pool...");
  vkDestroyCommandPool(this->_device, this->_commandPool, nullptr);

  LOG_DEBUG_SYS(RENDERING, "Destroying framebuffers...");
  for (auto framebuffer : this->_swapChainFramebuffers) {
    vkDestroyFramebuffer(this->_device, framebuffer, nullptr);
  }

  LOG_DEBUG_SYS(RENDERING, "Destroying pipeline...");
  vkDestroyPipeline(this->_device, this->_graphicsPipeline, nullptr);

  LOG_DEBUG_SYS(RENDERING, "Destroying pipeline layout...");
  vkDestroyPipelineLayout(this->_device, this->_pipelineLayout, nullptr);

  LOG_DEBUG_SYS(RENDERING, "Destroying render pass..");
  vkDestroyRenderPass(this->_device, this->_renderPass, nullptr);

  LOG_DEBUG_SYS(RENDERING, "Destroying shader modules...");
  vkDestroyShaderModule(this->_device, this->_fragShaderModule, nullptr);
  vkDestroyShaderModule(this->_device, this->_vertShaderModule, nullptr);

  LOG_DEBUG_SYS(RENDERING, "Destroying image views...");
  for (auto imageView : this->_swapChainImageViews) {
    vkDestroyImageView(this->_device, imageView, nullptr);
  }

  LOG_DEBUG_SYS(RENDERING, "Shutting down renderer...");
  vkDestroySurfaceKHR(this->_instance, this->_surface, nullptr);
  LOG_DEBUG_SYS(RENDERING, "Destroyed rendering surface.");
  vkDestroyDevice(this->_device, nullptr);
  LOG_DEBUG_SYS(RENDERING, "Destroyed logical device...");
  DestroyDebugUtilsMessengerEXT(this->_instance, this->_debugMessenger, nullptr);
  LOG_DEBUG_SYS(RENDERING, "Destroyed debug messenger.");
  vkDestroyInstance(this->_instance, nullptr);
  LOG_DEBUG_SYS(RENDERING, "Destroyed Vulkan instance.");
  SDL_DestroyWindow(this->_window);
  LOG_DEBUG_SYS(RENDERING, "Destroyed SDL window.");
  SDL_Quit();
  LOG_DEBUG_SYS(RENDERING, "Renderer shutdown completed.");
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
  this->_window =
      SDL_CreateWindow("Sprawl Engine (3D)", int(this->_screenWidth), int(this->_screenHeight), SDL_WINDOW_VULKAN);
  if (this->_window == nullptr) {
    LOG_FATAL_SYS(SDL, "Window could not be created! {0}", Logging::getSDLError());
    throw;
  }
  createVulkanInstance();
  setupDebugMessenger();
  createSurface();
  pickPhysicalDevice();
  createLogicalDevice();
  createSwapChain();
  createImageViews();
  createGraphicsPipelineLayout();
  createRenderPass();
  createGraphicsPipeline();
  createFramebuffers();
  createCommandPool();
  createCommandBuffer();
}

void GraphicsManager3D::gameLoopUpdate(const time_ms duration) { (void)duration; }

void GraphicsManager3D::createVulkanInstance() {
  if (!checkVulkanValidationLayerSupport()) {
    throw std::runtime_error("validation layers requested, but not available!");
  }

  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Sprawl Engine (3D)";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "Sprawl Engine (3D)";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  // TODO: This is C-style and copy/pasted here from the SDL wiki to get this shit working
  // https://wiki.libsdl.org/SDL3/SDL_Vulkan_GetInstanceExtensions

  // Retrieve Vulkan instance extensions
  unsigned int extensionCount = 0;
  const char* const* SDLExtensions = SDL_Vulkan_GetInstanceExtensions(&extensionCount);

  if (SDLExtensions == nullptr) {
    throw std::runtime_error("failed to get extensions!");
  }
  for (unsigned int i = 0; i < extensionCount; i++) {
    this->_instanceExtensions.push_back(SDLExtensions[i]);
  }

  LOG_DEBUG_SYS(RENDERING, "Vulkan instance extensions enabled:");
  for (auto extension : this->_instanceExtensions) {
    LOG_DEBUG_SYS(RENDERING, extension);
  }

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  createInfo.enabledExtensionCount = static_cast<uint32_t>(this->_instanceExtensions.size());
  createInfo.ppEnabledExtensionNames = this->_instanceExtensions.data();
  createInfo.enabledLayerCount = static_cast<uint32_t>(VALIDATION_LAYERS.size());
  createInfo.ppEnabledLayerNames = VALIDATION_LAYERS.data();

  // TODO: We want validation layer coverage around instance creation and destruction too
  // see: https://vulkan-tutorial.com/en/Drawing_a_triangle/Setup/Validation_layers
  VkResult result = vkCreateInstance(&createInfo, nullptr, &this->_instance);
  if (result) {
    throw std::runtime_error("failed to create instance!");
  }
  LOG_DEBUG_SYS(RENDERING, "Created Vulkan instance!");
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

  LOG_DEBUG_SYS(VULKAN, pCallbackData->pMessage);
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
    LOG_DEBUG_SYS(VULKAN, "Creating debug messenger.");
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  } else {
    LOG_FATAL_SYS(VULKAN, "Could not create debug messenger function!");
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}

void GraphicsManager3D::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                                      const VkAllocationCallbacks* pAllocator) {
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr) {
    func(instance, debugMessenger, pAllocator);
    LOG_DEBUG_SYS(VULKAN, "Destroyed debug messenger.");
  }
}

void GraphicsManager3D::pickPhysicalDevice() {
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(this->_instance, &deviceCount, nullptr);
  if (deviceCount == 0) {
    throw std::runtime_error("Failed to find GPUs with Vulkan support!");
  }
  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(this->_instance, &deviceCount, devices.data());

  for (const auto& device : devices) {
    if (isDeviceSuitable(device)) {
      this->_physicalDevice = device;
      return;
    }
  }

  throw std::runtime_error("Failed to find a suitable GPU!");
}

bool GraphicsManager3D::isDeviceSuitable(VkPhysicalDevice device) {
  QueueFamilyIndices indices = this->findQueueFamilies(device);
  bool extensionsSupported = checkDeviceExtensionSupport(device);

  bool swapChainAdequate = false;
  if (extensionsSupported) {
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
    swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
  }

  return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

bool GraphicsManager3D::checkDeviceExtensionSupport(VkPhysicalDevice device) {
  uint32_t extensionCount;
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

  std::vector<VkExtensionProperties> availableExtensions(extensionCount);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

  std::set<std::string> requiredExtensions(this->_deviceExtensions.begin(), this->_deviceExtensions.end());

  for (const auto& extension : availableExtensions) {
    LOG_DEBUG_SYS(RENDERING, "Required device extenion found: {0}", extension.extensionName);
    requiredExtensions.erase(extension.extensionName);
  }

  return requiredExtensions.empty();
}

QueueFamilyIndices GraphicsManager3D::findQueueFamilies(VkPhysicalDevice device) {
  QueueFamilyIndices indices;
  uint32_t queueFamilyCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

  VkBool32 presentSupport = false;

  for (uint32_t i = 0; i < queueFamilies.size(); i++) {
    VkQueueFlags flags = queueFamilies[i].queueFlags;
    if (flags & VK_QUEUE_GRAPHICS_BIT) {
      indices.graphicsFamily = i;
    }

    vkGetPhysicalDeviceSurfaceSupportKHR(device, i, this->_surface, &presentSupport);
    if (presentSupport) {
      indices.presentFamily = i;
    }
  }

  return indices;
}

void GraphicsManager3D::createLogicalDevice() {
  // TODO: This is redundant since we're doing it above during physical device selection
  // (copy/pasted tutorial code).
  QueueFamilyIndices indices = findQueueFamilies(this->_physicalDevice);

  std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
  std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

  float queuePriority = 1.0f;

  for (uint32_t queueFamily : uniqueQueueFamilies) {
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamily;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;
    queueCreateInfos.push_back(queueCreateInfo);
    LOG_DEBUG_SYS(RENDERING, "Added queue creation request for family {0}", queueFamily);
  }

  // No special device features needed for now
  VkPhysicalDeviceFeatures deviceFeatures{};

  VkDeviceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  createInfo.pQueueCreateInfos = queueCreateInfos.data();
  createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
  createInfo.enabledExtensionCount = static_cast<uint32_t>(this->_deviceExtensions.size());
  createInfo.ppEnabledExtensionNames = this->_deviceExtensions.data();
  createInfo.pEnabledFeatures = &deviceFeatures;

  // TODO: This should be configurable (if validation is enabled)
  createInfo.enabledLayerCount = static_cast<uint32_t>(VALIDATION_LAYERS.size());
  createInfo.ppEnabledLayerNames = VALIDATION_LAYERS.data();

  if (vkCreateDevice(this->_physicalDevice, &createInfo, nullptr, &this->_device) != VK_SUCCESS) {
    throw std::runtime_error("failed to create logical device!");
  }
  vkGetDeviceQueue(this->_device, indices.graphicsFamily.value(), 0, &this->_graphicsQueue);
  vkGetDeviceQueue(this->_device, indices.presentFamily.value(), 0, &this->_presentQueue);
}

void GraphicsManager3D::createSurface() {
  SDL_bool res = SDL_Vulkan_CreateSurface(this->_window, this->_instance, nullptr, &this->_surface);
  // NOTE: Confusingly SDL_TRUE is 1 and also the value returned on correct exit;
  // not the same as most other return codes which are 0 on correct exit.
  if (res != SDL_TRUE) {
    LOG_FATAL_SYS(RENDERING, SDL_GetError());
    throw std::runtime_error("failed to create rendering surface!");
  }
}

SwapChainSupportDetails GraphicsManager3D::querySwapChainSupport(VkPhysicalDevice candidateDevice) {
  SwapChainSupportDetails details;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(candidateDevice, this->_surface, &details.capabilities);

  uint32_t formatCount;
  vkGetPhysicalDeviceSurfaceFormatsKHR(candidateDevice, this->_surface, &formatCount, nullptr);

  if (formatCount != 0) {
    details.formats.resize(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(candidateDevice, this->_surface, &formatCount, details.formats.data());
  }

  uint32_t presentModeCount;
  vkGetPhysicalDeviceSurfacePresentModesKHR(candidateDevice, this->_surface, &presentModeCount, nullptr);

  if (presentModeCount != 0) {
    details.presentModes.resize(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(candidateDevice, this->_surface, &presentModeCount,
                                              details.presentModes.data());
  }

  return details;
}

VkSurfaceFormatKHR GraphicsManager3D::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
  // https://stackoverflow.com/questions/12524623/what-are-the-practical-differences-when-working-with-colors-in-a-linear-vs-a-no
  for (const auto& availableFormat : availableFormats) {
    if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
        availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
      return availableFormat;
    }
  }
  return availableFormats[0];
}

VkPresentModeKHR GraphicsManager3D::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
  for (const auto& availablePresentMode : availablePresentModes) {
    // Prefer mailbox mode for triple buffering, otherwise just use
    // FIFO mode to force vsync
    if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
      return availablePresentMode;
    }
  }
  return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D GraphicsManager3D::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
  if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
    return capabilities.currentExtent;
  } else {
    int width, height;
    SDL_GetWindowSizeInPixels(this->_window, &width, &height);

    VkExtent2D actualExtent = {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
    actualExtent.width =
        std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    actualExtent.height =
        std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

    return actualExtent;
  }
}

void GraphicsManager3D::createSwapChain() {
  SwapChainSupportDetails swapChainSupport = querySwapChainSupport(this->_physicalDevice);

  this->_swapChainImageFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
  VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
  this->_swapChainExtent = chooseSwapExtent(swapChainSupport.capabilities);

  // One more than the minimum so we aren't stuck waiting on the driver to complete before we can aquire
  // another image.
  uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
  if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
    imageCount = swapChainSupport.capabilities.maxImageCount;
  }

  VkSwapchainCreateInfoKHR createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  createInfo.surface = this->_surface;
  createInfo.minImageCount = imageCount;
  createInfo.imageFormat = this->_swapChainImageFormat.format;
  createInfo.imageColorSpace = this->_swapChainImageFormat.colorSpace;
  createInfo.imageExtent = this->_swapChainExtent;
  createInfo.imageArrayLayers = 1;
  createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

  // Determine how swap chain images are used across multiple queues (if queues differ)
  QueueFamilyIndices indices = findQueueFamilies(this->_physicalDevice);
  uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};
  if (indices.graphicsFamily != indices.presentFamily) {
    createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    createInfo.queueFamilyIndexCount = 2;
    createInfo.pQueueFamilyIndices = queueFamilyIndices;
  } else {
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.queueFamilyIndexCount = 0;      // Optional
    createInfo.pQueueFamilyIndices = nullptr;  // Optional
  }
  createInfo.preTransform = swapChainSupport.capabilities.currentTransform;  // Don't transform image
  createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;             // Ignore alpha, don't blend
  createInfo.presentMode = presentMode;
  createInfo.clipped = VK_TRUE;
  createInfo.oldSwapchain = VK_NULL_HANDLE;

  if (vkCreateSwapchainKHR(this->_device, &createInfo, nullptr, &this->_swapChain) != VK_SUCCESS) {
    throw std::runtime_error("failed to create swap chain!");
  }

  // Example of how to get swapchain images; remove this later.
  vkGetSwapchainImagesKHR(this->_device, this->_swapChain, &imageCount, nullptr);
  this->_swapChainImages.resize(imageCount);
  vkGetSwapchainImagesKHR(this->_device, this->_swapChain, &imageCount, this->_swapChainImages.data());
}

void GraphicsManager3D::createImageViews() {
  this->_swapChainImageViews.resize(this->_swapChainImages.size());
  for (size_t i = 0; i < this->_swapChainImages.size(); i++) {
    VkImageViewCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.image = this->_swapChainImages[i];
    createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    createInfo.format = this->_swapChainImageFormat.format;
    createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    if (vkCreateImageView(this->_device, &createInfo, nullptr, &this->_swapChainImageViews[i]) != VK_SUCCESS) {
      throw std::runtime_error("failed to create image views!");
    }
  }
}

static std::vector<char> readFile(const std::string& filename) {
  std::ifstream file(filename, std::ios::ate | std::ios::binary);

  if (!file.is_open()) {
    throw std::runtime_error("failed to open file!");
  }

  size_t fileSize = (size_t)file.tellg();
  std::vector<char> buffer(fileSize);
  file.seekg(0);
  file.read(buffer.data(), (std::streamsize)fileSize);
  file.close();

  return buffer;
}

VkShaderModule GraphicsManager3D::createShaderModule(const std::vector<char>& code) {
  VkShaderModuleCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  createInfo.codeSize = code.size();
  createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

  VkShaderModule shaderModule;
  if (vkCreateShaderModule(this->_device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
    throw std::runtime_error("failed to create shader module!");
  }

  return shaderModule;
}

void GraphicsManager3D::createGraphicsPipelineLayout() {
  auto vertShaderCode = readFile("bin/shaders/shader.vert.spv");
  auto fragShaderCode = readFile("bin/shaders/shader.frag.spv");

  this->_vertShaderModule = createShaderModule(vertShaderCode);
  this->_fragShaderModule = createShaderModule(fragShaderCode);

  VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
  vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
  vertShaderStageInfo.module = this->_vertShaderModule;
  vertShaderStageInfo.pName = "main";
  this->_shaderStages[0] = vertShaderStageInfo;

  VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
  fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  fragShaderStageInfo.module = this->_fragShaderModule;
  fragShaderStageInfo.pName = "main";
  this->_shaderStages[1] = fragShaderStageInfo;

  VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
  pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutInfo.setLayoutCount = 0;             // Optional
  pipelineLayoutInfo.pSetLayouts = nullptr;          // Optional
  pipelineLayoutInfo.pushConstantRangeCount = 0;     // Optional
  pipelineLayoutInfo.pPushConstantRanges = nullptr;  // Optional

  if (vkCreatePipelineLayout(this->_device, &pipelineLayoutInfo, nullptr, &this->_pipelineLayout) != VK_SUCCESS) {
    throw std::runtime_error("failed to create pipeline layout!");
  }
}

void GraphicsManager3D::createRenderPass() {
  VkAttachmentDescription colorAttachment{};
  colorAttachment.format = this->_swapChainImageFormat.format;
  colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
  colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  VkAttachmentReference colorAttachmentRef{};
  colorAttachmentRef.attachment = 0;
  colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  VkSubpassDescription subpass{};
  subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments = &colorAttachmentRef;

  VkRenderPassCreateInfo renderPassInfo{};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  renderPassInfo.attachmentCount = 1;
  renderPassInfo.pAttachments = &colorAttachment;
  renderPassInfo.subpassCount = 1;
  renderPassInfo.pSubpasses = &subpass;

  if (vkCreateRenderPass(this->_device, &renderPassInfo, nullptr, &this->_renderPass) != VK_SUCCESS) {
    throw std::runtime_error("failed to create render pass!");
  }
}

void GraphicsManager3D::createGraphicsPipeline() {
  // Configure vertex data loading; presently we're hardcoding vertex data in
  // the shaders so this step can be skipped
  VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
  vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertexInputInfo.vertexBindingDescriptionCount = 0;
  vertexInputInfo.pVertexBindingDescriptions = nullptr;  // Optional
  vertexInputInfo.vertexAttributeDescriptionCount = 0;
  vertexInputInfo.pVertexAttributeDescriptions = nullptr;  // Optional

  // configure input assembly to draw triangles
  VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
  inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  inputAssembly.primitiveRestartEnable = VK_FALSE;

  // Configure dynamic state
  std::vector<VkDynamicState> dynamicStates = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};

  VkPipelineDynamicStateCreateInfo dynamicState{};
  dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
  dynamicState.pDynamicStates = dynamicStates.data();

  // Configure viewport
  VkViewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = (float)this->_swapChainExtent.width;
  viewport.height = (float)this->_swapChainExtent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  VkRect2D scissor{};
  scissor.offset = {0, 0};
  scissor.extent = this->_swapChainExtent;

  VkPipelineViewportStateCreateInfo viewportState{};
  viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewportState.viewportCount = 1;
  viewportState.pViewports = &viewport;
  viewportState.scissorCount = 1;
  viewportState.pScissors = &scissor;

  // Configure rasterizer (takes geometry shaped by vertices from vertex shader and turns
  // it into fragments colored by fragment shader)
  VkPipelineRasterizationStateCreateInfo rasterizer{};
  rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer.depthClampEnable = VK_FALSE;
  rasterizer.rasterizerDiscardEnable = VK_FALSE;
  rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
  rasterizer.lineWidth = 1.0f;
  rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
  rasterizer.depthBiasEnable = VK_FALSE;
  rasterizer.depthBiasConstantFactor = 0.0f;  // Optional
  rasterizer.depthBiasClamp = 0.0f;           // Optional
  rasterizer.depthBiasSlopeFactor = 0.0f;     // Optional

  // Configure multisampling
  VkPipelineMultisampleStateCreateInfo multisampling{};
  multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable = VK_FALSE;
  multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
  multisampling.minSampleShading = 1.0f;           // Optional
  multisampling.pSampleMask = nullptr;             // Optional
  multisampling.alphaToCoverageEnable = VK_FALSE;  // Optional
  multisampling.alphaToOneEnable = VK_FALSE;       // Optional

  // Configure color blending
  VkPipelineColorBlendAttachmentState colorBlendAttachment{};
  colorBlendAttachment.colorWriteMask =
      VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  colorBlendAttachment.blendEnable = VK_TRUE;
  colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
  colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
  colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
  colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
  colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

  VkPipelineColorBlendStateCreateInfo colorBlending{};
  colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  colorBlending.logicOpEnable = VK_FALSE;
  colorBlending.logicOp = VK_LOGIC_OP_COPY;  // Optional
  colorBlending.attachmentCount = 1;
  colorBlending.pAttachments = &colorBlendAttachment;
  colorBlending.blendConstants[0] = 0.0f;  // Optional
  colorBlending.blendConstants[1] = 0.0f;  // Optional
  colorBlending.blendConstants[2] = 0.0f;  // Optional
  colorBlending.blendConstants[3] = 0.0f;  // Optional

  VkGraphicsPipelineCreateInfo pipelineInfo{};
  pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipelineInfo.stageCount = 2;
  pipelineInfo.pStages = this->_shaderStages;
  pipelineInfo.layout = this->_pipelineLayout;
  pipelineInfo.renderPass = this->_renderPass;
  pipelineInfo.subpass = 0;
  pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;  // Optional
  pipelineInfo.basePipelineIndex = -1;               // Optional
  pipelineInfo.pVertexInputState = &vertexInputInfo;
  pipelineInfo.pInputAssemblyState = &inputAssembly;
  pipelineInfo.pViewportState = &viewportState;
  pipelineInfo.pRasterizationState = &rasterizer;
  pipelineInfo.pMultisampleState = &multisampling;
  pipelineInfo.pDepthStencilState = nullptr;  // Optional
  pipelineInfo.pColorBlendState = &colorBlending;
  pipelineInfo.pDynamicState = &dynamicState;

  if (vkCreateGraphicsPipelines(this->_device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &this->_graphicsPipeline) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to create graphics pipeline!");
  }
}

void GraphicsManager3D::createFramebuffers() {
  this->_swapChainFramebuffers.resize(this->_swapChainImageViews.size());
  for (size_t i = 0; i < this->_swapChainImageViews.size(); i++) {
    VkImageView attachments[] = {this->_swapChainImageViews[i]};

    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = this->_renderPass;
    framebufferInfo.attachmentCount = 1;
    framebufferInfo.pAttachments = attachments;
    framebufferInfo.width = this->_swapChainExtent.width;
    framebufferInfo.height = this->_swapChainExtent.height;
    framebufferInfo.layers = 1;

    if (vkCreateFramebuffer(this->_device, &framebufferInfo, nullptr, &this->_swapChainFramebuffers[i]) != VK_SUCCESS) {
      throw std::runtime_error("failed to create framebuffer!");
    }
  }
}

void GraphicsManager3D::createCommandPool() {
  QueueFamilyIndices queueFamilyIndices = findQueueFamilies(this->_physicalDevice);

  VkCommandPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

  if (vkCreateCommandPool(this->_device, &poolInfo, nullptr, &this->_commandPool) != VK_SUCCESS) {
    throw std::runtime_error("failed to create command pool!");
  }
}

void GraphicsManager3D::createCommandBuffer() {
  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = this->_commandPool;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandBufferCount = 1;

  if (vkAllocateCommandBuffers(this->_device, &allocInfo, &this->_commandBuffer) != VK_SUCCESS) {
    throw std::runtime_error("failed to allocate command buffers!");
  }
}

void GraphicsManager3D::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = 0;                   // Optional
  beginInfo.pInheritanceInfo = nullptr;  // Optional

  if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
    throw std::runtime_error("failed to begin recording command buffer!");
  }

  VkRenderPassBeginInfo renderPassInfo{};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderPassInfo.renderPass = this->_renderPass;
  renderPassInfo.framebuffer = this->_swapChainFramebuffers[imageIndex];
  renderPassInfo.renderArea.offset = {0, 0};
  renderPassInfo.renderArea.extent = this->_swapChainExtent;

  VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
  renderPassInfo.clearValueCount = 1;
  renderPassInfo.pClearValues = &clearColor;

  vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
  vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, this->_graphicsPipeline);

  VkViewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = static_cast<float>(this->_swapChainExtent.width);
  viewport.height = static_cast<float>(this->_swapChainExtent.height);
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;
  vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

  VkRect2D scissor{};
  scissor.offset = {0, 0};
  scissor.extent = this->_swapChainExtent;
  vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

  // ACTUALLY DRAW THE TRIANGLE, TA-DA!!!
  vkCmdDraw(commandBuffer, 3, 1, 0, 0);

  vkCmdEndRenderPass(commandBuffer);
  if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
    throw std::runtime_error("failed to record command buffer!");
  }
}

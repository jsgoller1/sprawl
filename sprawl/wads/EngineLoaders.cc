#include <memory>
#include <string>

#include "GraphicsSettings.hh"
#include "InputHandler.hh"
#include "WADLoader.hh"
#include "World.hh"

void WADLoader::loadLogging() const {
  if (!this->_jsonBody.contains("logging")) {
    LOG_INFO_SYS(WADLOADER, "No logging configs present.");
    return;
  }
  nlohmann::json loggingConfig = this->_jsonBody["logging"];
  Logging::setDefaultLogLevel(Logging::toLogLevel(loggingConfig.value("defaultLogLevel", "WARN")));
  Logging::setColorUse(loggingConfig.value("useColor", true));

  if (loggingConfig.contains("overrides")) {
    for (auto override : loggingConfig["overrides"]) {
      if ((override.contains("system") && override.contains("logLevel"))) {
        Logging::setOverrideSubsystem(Logging::toLoggingSubsystem(override["system"]),
                                      Logging::toLogLevel(override["logLevel"]));
      } else if ((override.contains("entity") && override.contains("logLevel"))) {
        Logging::setOverrideEntity(override["entity"], Logging::toLogLevel(override["logLevel"]));
      } else {
        LOG_WARN_SYS(WADLOADER, "Skipping override: {0}", std::string(override));
      }
    }
  }
}

GraphicsSettings WADLoader::loadGraphicsSettings(const nlohmann::json& jsonBody) const {
  ScreenWidth width = loadKey<ScreenWidth>(jsonBody, "screenWidth", 800);
  ScreenHeight height = loadKey<ScreenHeight>(jsonBody, "screenHeight", width - (width / 4));
  bool useHardwareAcceleration = loadKey<bool>(jsonBody, "useHardwareAcceleration", true);
  bool useVSync = loadKey<bool>(jsonBody, "useVSync", true);
  return GraphicsSettings{.screenWidth = width,
                          .screenHeight = height,
                          .useHardwareAcceleration = useHardwareAcceleration,
                          .useVSync = useVSync};
}

std::shared_ptr<InputHandler> WADLoader::loadInputHandler() const {
  return std::shared_ptr<InputHandler>(new InputHandler());
}

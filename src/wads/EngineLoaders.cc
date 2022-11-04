#include "InputHandler.hh"
#include "Screen.hh"
#include "WADLoader.hh"
#include "World.hh"

void WADLoader::loadLogging() const {
  if (!this->_jsonBody.contains("logging")) {
    LOG_INFO_SYS(WADLOADER, "No logging configs present.");
    return;
  }
  json loggingConfig = this->_jsonBody["logging"];
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
        LOG_WARN_SYS(WADLOADER, "Skipping override: {0}", string(override));
      }
    }
  }
}

shared_ptr<World> WADLoader::loadWorld() const {
  shared_ptr<Zone> zone = this->loadZone(this->_jsonBody["zones"][0]);
  return shared_ptr<World>(new World(zone));
}

shared_ptr<Screen> WADLoader::loadScreen() const {
  ScreenWidth width;
  ScreenHeight height;
  if (this->_jsonBody.contains("screen")) {
    json screenJSON = this->_jsonBody["screen"];
    width = loadKey<ScreenWidth>(screenJSON, "width", 800);
    height = loadKey<ScreenHeight>(screenJSON, "height", width - (width / 4));
  } else {
    LOG_ERROR("Cannot find 'screen' section in WAD; will set screen size to 800x600");
    width = 800;
    height = 600;
  }
  return shared_ptr<Screen>(new Screen(width, height));
}

shared_ptr<InputHandler> WADLoader::loadInputHandler() const { return shared_ptr<InputHandler>(new InputHandler()); }

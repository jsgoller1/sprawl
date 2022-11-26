#include <map>
#include <string>

#include "Logging.hh"
#include "SDL2/SDL.h"

static std::map<LogLevel, std::string> logLevelNames = std::map<LogLevel, std::string>{{FATAL, std::string("FATAL")},
                                                                                       {ERROR, std::string("ERROR")},
                                                                                       {WARN, std::string("WARN")},
                                                                                       {INFO, std::string("INFO")},
                                                                                       {DEBUG, std::string("DEBUG")}};

static std::map<LoggingSubsystem, std::string> subsystemNames = std::map<LoggingSubsystem, std::string>{
    {NONE, "NONE"},           {COLLISIONS, "COLLISIONS"}, {INPUT, "INPUT"},         {LOGGING, "LOGGING"},
    {MATH, "MATH"},           {PHYSICS, "PHYSICS"},       {RENDERING, "RENDERING"}, {SDL, "SDL"},
    {WADLOADER, "WADLOADER"}, {WORLD, "WORLD"},           {ZONE, "ZONE"},
};

std::string Logging::getName(const LoggingSubsystem& subsystem) { return subsystemNames[subsystem]; }
std::string Logging::getName(const LogLevel& level) { return logLevelNames[level]; }

LogLevel Logging::toLogLevel(const std::string& name) {
  for (auto p : logLevelNames) {
    if (p.second == name) {
      return p.first;
    }
  }
  LOG_ERROR_SYS(LOGGING, "Couldn't associate name with {0}, defaulting to 'DEBUG'", name);
  return DEBUG;
}

LoggingSubsystem Logging::toLoggingSubsystem(const std::string& name) {
  for (auto p : subsystemNames) {
    if (p.second == name) {
      return p.first;
    }
  }
  LOG_ERROR_SYS(LOGGING, "Couldn't associate a subsystem name with '{0}', defaulting to 'NONE'", name);
  return NONE;
}

/*
 * Grabs error message from SDL and returns it as a std::string.
 */
std::string Logging::getSDLError() {
  std::string error = std::string(SDL_GetError());
  SDL_ClearError();
  return error;
}

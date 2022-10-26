#include <SDL2/SDL.h>

#include <map>
#include <string>

#include "Logging.hh"

using std::map;
using std::string;

static map<LogLevel, string> logLevelNames =
    map<LogLevel, string>{{FATAL, string("FATAL")},
                          {ERROR, string("ERROR")},
                          {WARN, string("WARN")},
                          {INFO, string("INFO")},
                          {DEBUG, string("DEBUG")}};

static map<LoggingSubsystem, string> subsystemNames =
    map<LoggingSubsystem, string>{
        {NONE, "NONE"},           {COLLISIONS, "COLLISIONS"},
        {INPUT, "INPUT"},         {LOGGING, "LOGGING"},
        {MATH, "MATH"},           {PHYSICS, "PHYSICS"},
        {RENDERING, "RENDERING"}, {SDL, "SDL"},
        {WADLOADER, "WADLOADER"}, {WORLD, "WORLD"},
        {ZONE, "ZONE"},
    };

string Logging::getName(const LoggingSubsystem& subsystem) {
  return subsystemNames[subsystem];
}
string Logging::getName(const LogLevel& level) { return logLevelNames[level]; }

LogLevel Logging::toLogLevel(const string& name) {
  for (auto p : logLevelNames) {
    if (p.second == name) {
      return p.first;
    }
  }
  LOG_ERROR_SYS(
      LOGGING, "Couldn't associate name with {0}, defaulting to 'DEBUG'", name);
  return DEBUG;
}

LoggingSubsystem Logging::toLoggingSubsystem(const string& name) {
  for (auto p : subsystemNames) {
    if (p.second == name) {
      return p.first;
    }
  }
  LOG_ERROR_SYS(
      LOGGING,
      "Couldn't associate a subsystem name with '{0}', defaulting to 'NONE'",
      name);
  return NONE;
}

/*
 * Grabs error message from SDL and returns it as a string.
 */
string Logging::getSDLError() {
  string error = string(SDL_GetError());
  SDL_ClearError();
  return error;
}

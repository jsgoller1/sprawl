#include <map>

#include "Logging.hh"

using std::map;

static LogLevel defaultLevel = LogLevel::WARN;
static std::map<LoggingSubsystem, LogLevel> subsystemOverrides = std::map<LoggingSubsystem, LogLevel>();
static std::map<std::string, LogLevel> entityOverrides = std::map<std::string, LogLevel>();
static std::map<std::string, LogLevel> fileOverrides = std::map<std::string, LogLevel>();
static std::map<std::string, LogLevel> funcOverrides = std::map<std::string, LogLevel>();

LogLevel Logging::getDefaultLogLevel() { return defaultLevel; }
void Logging::setDefaultLogLevel(const LogLevel &level) { defaultLevel = level; }

LogLevel Logging::getOverrideSubsystem(const LoggingSubsystem &system) {
  if (subsystemOverrides.find(system) == subsystemOverrides.end()) {
    LOG_WARN("No override set for {0}, returning default log level ().");
    return defaultLevel;
  }

  return subsystemOverrides[system];
}
void Logging::setOverrideSubsystem(const LoggingSubsystem &systemName, const LogLevel &level) {
  subsystemOverrides[systemName] = level;
}

LogLevel Logging::getOverrideEntity(const std::string &entityName) {
  if (entityOverrides.find(entityName) == entityOverrides.end()) {
    LOG_WARN("No override set for {0}, returning default log level ().");
    return defaultLevel;
  }

  return entityOverrides[entityName];
}
void Logging::setOverrideEntity(const std::string &entityName, const LogLevel &level) {
  entityOverrides[entityName] = level;
}

LogLevel Logging::getOverrideFile(const std::string &fileName) {
  if (fileOverrides.find(fileName) == fileOverrides.end()) {
    LOG_WARN("No override set for {0}, returning default log level ().");
    return defaultLevel;
  }

  return fileOverrides[fileName];
}
void Logging::setOverrideFile(const std::string &fileName, const LogLevel &level) { fileOverrides[fileName] = level; }

LogLevel Logging::getOverrideFunc(const std::string &funcName) {
  if (funcOverrides.find(funcName) == funcOverrides.end()) {
    LOG_WARN("No override set for {0}, returning default log level ().");
    return defaultLevel;
  }

  return funcOverrides[funcName];
}
void Logging::setOverrideFunc(const std::string &funcName, const LogLevel &level) { funcOverrides[funcName] = level; }

bool Logging::shouldLoggingOccur(const LogLevel &level, const std::string &funcName, const std::string &fileName,
                                 const std::string &entityName, const LoggingSubsystem subsystem) {
  if (funcOverrides.find(funcName) != funcOverrides.end()) {
    return level >= funcOverrides[funcName];
  }

  if (fileOverrides.find(fileName) != fileOverrides.end()) {
    return level >= fileOverrides[fileName];
  }

  if (entityOverrides.find(entityName) != entityOverrides.end()) {
    return level >= entityOverrides[entityName];
  }

  if (subsystemOverrides.find(subsystem) != subsystemOverrides.end()) {
    return level >= subsystemOverrides[subsystem];
  }

  return level >= defaultLevel;
}

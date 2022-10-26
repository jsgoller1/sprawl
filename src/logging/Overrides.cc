#include <map>

#include "Logging.hh"

using std::map;

static LogLevel defaultLevel = LogLevel::WARN;
static map<LoggingSubsystem, LogLevel> subsystemOverrides = map<LoggingSubsystem, LogLevel>();
static map<string, LogLevel> entityOverrides = map<string, LogLevel>();
static map<string, LogLevel> fileOverrides = map<string, LogLevel>();
static map<string, LogLevel> funcOverrides = map<string, LogLevel>();

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

LogLevel Logging::getOverrideEntity(const string &entityName) {
  if (entityOverrides.find(entityName) == entityOverrides.end()) {
    LOG_WARN("No override set for {0}, returning default log level ().");
    return defaultLevel;
  }

  return entityOverrides[entityName];
}
void Logging::setOverrideEntity(const string &entityName, const LogLevel &level) {
  entityOverrides[entityName] = level;
}

LogLevel Logging::getOverrideFile(const string &fileName) {
  if (fileOverrides.find(fileName) == fileOverrides.end()) {
    LOG_WARN("No override set for {0}, returning default log level ().");
    return defaultLevel;
  }

  return fileOverrides[fileName];
}
void Logging::setOverrideFile(const string &fileName, const LogLevel &level) { fileOverrides[fileName] = level; }

LogLevel Logging::getOverrideFunc(const string &funcName) {
  if (funcOverrides.find(funcName) == funcOverrides.end()) {
    LOG_WARN("No override set for {0}, returning default log level ().");
    return defaultLevel;
  }

  return funcOverrides[funcName];
}
void Logging::setOverrideFunc(const string &funcName, const LogLevel &level) { funcOverrides[funcName] = level; }

bool Logging::shouldLoggingOccur(const LogLevel &level, const string &funcName, const string &fileName,
                                 const string &entityName, const LoggingSubsystem subsystem) {
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

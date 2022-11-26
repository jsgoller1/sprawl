#pragma once

#include <iostream>
#include <string>

#include "LoggingTypes.hh"
#include "Macros.hh"
#include "fmt/color.h"
#include "fmt/format.h"

#define DEFAULT_LOGGING_LEVEL LogLevel::Warn()
#define DEFAULT_USE_COLORS true
#define DEFAULT_QUIET false

#define NO_ENTITY_GIVEN "__NO_ENTITY_GIVEN__"

namespace Logging {

// Settings
void setShowTime(const bool &setting);
bool getShowTime();
void setShowLogLevel(const bool &setting);
bool getShowLogLevel();
void setShowSubsystemName(const bool &setting);
bool getShowSubsystemName();
void setShowEntityName(const bool &setting);
bool getShowEntityName();
void setShowFile(const bool &setting);
bool getShowFile();
void setShowFuncName(const bool &setting);
bool getShowFuncName();
void setColorUse(const bool &setting);
bool getColorUse();

// Overrides
void setDefaultLogLevel(const LogLevel &level);
LogLevel getDefaultLogLevel();
void setOverrideSubsystem(const LoggingSubsystem &subsystem, const LogLevel &level);
LogLevel getOverrideSubsystem(const LoggingSubsystem &systemName);
void setOverrideEntity(const std::string &entityName, const LogLevel &level);
LogLevel getOverrideEntity(const std::string &entityName);
void setOverrideFile(const std::string &fileName, const LogLevel &level);
LogLevel getOverrideFile(const std::string &fileName);
void setOverrideFunc(const std::string &funcName, const LogLevel &level);
LogLevel getOverrideFunc(const std::string &funcName);
bool shouldLoggingOccur(const LogLevel &level, const std::string &funcName, const std::string &fileName,
                        const std::string &entityName, const LoggingSubsystem subsystem);

// Helpers
std::string getName(const LoggingSubsystem &subsystem);
std::string getName(const LogLevel &level);
LogLevel toLogLevel(const std::string &name);
LoggingSubsystem toLoggingSubsystem(const std::string &name);
std::string getSDLError();

/*
 * Implementation of Log(). Do not call directly.
 */
void impl_Log(const std::string &fileName, const int lineNo, const std::string &funcName, const LogLevel &level,
              const LoggingSubsystem subsystem, const std::string &entityName, const std::string &format,
              fmt::format_args &fargs);

/*
 * Multi-purpose logging function providing filtering based on subsystem,
 * entity name, and log level. Provides text coloring. Use the LOG_* macros
 * instead of calling this function directly (though it's fine if necessary,
 * just inconvenient and harder to read).
 */
template <typename... Args>
void Log(const std::string &fileName, const int lineNo, const std::string &funcName, const LogLevel &level,
         const LoggingSubsystem subsystem, const std::string &entityName, const std::string &format, Args &&...args) {
  fmt::format_args fargs = fmt::make_format_args(args...);
  impl_Log(fileName, lineNo, funcName, level, subsystem, entityName, format, fargs);
}

}  // namespace Logging

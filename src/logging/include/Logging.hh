#pragma once

#include <iostream>
#include <string>
using std::string;

#include "LoggingTypes.hh"
#include "Macros.hh"
#include "color.h"
#include "format.h"

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
void setOverrideSubsystem(const LoggingSubsystem &subsystem,
                          const LogLevel &level);
LogLevel getOverrideSubsystem(const LoggingSubsystem &systemName);
void setOverrideEntity(const string &entityName, const LogLevel &level);
LogLevel getOverrideEntity(const string &entityName);
void setOverrideFile(const string &fileName, const LogLevel &level);
LogLevel getOverrideFile(const string &fileName);
void setOverrideFunc(const string &funcName, const LogLevel &level);
LogLevel getOverrideFunc(const string &funcName);
bool shouldLoggingOccur(const LogLevel &level, const string &funcName,
                        const string &fileName, const string &entityName,
                        const LoggingSubsystem subsystem);

// Helpers
string getName(const LoggingSubsystem &subsystem);
string getName(const LogLevel &level);
LogLevel toLogLevel(const string &name);
LoggingSubsystem toLoggingSubsystem(const string &name);
string getSDLError();

/*
 * Implementation of Log(). Do not call directly.
 */
void impl_Log(const string &fileName, const int lineNo, const string &funcName,
              const LogLevel &level, const LoggingSubsystem subsystem,
              const string &entityName, const string &format,
              fmt::format_args &fargs);

/*
 * Multi-purpose logging function providing filtering based on subsystem,
 * entity name, and log level. Provides text coloring. Use the LOG_* macros
 * instead of calling this function directly (though it's fine if necessary,
 * just inconvenient and harder to read).
 */
template <typename... Args>
void Log(const string &fileName, const int lineNo, const string &funcName,
         const LogLevel &level, const LoggingSubsystem subsystem,
         const string &entityName, const string &format, Args &&...args) {
  fmt::format_args fargs = fmt::make_format_args(args...);
  impl_Log(fileName, lineNo, funcName, level, subsystem, entityName, format,
           fargs);
}

}  // namespace Logging

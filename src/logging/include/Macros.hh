#pragma once

/*
 * Unrecoverable situation, engine crash imminent. OwO n-n-no likey crashy-washy, Sprawl-daddy. Pwease don't hwurt me!!!
 * 🥺👉👈 (Respects overrides: file name, function name)
 */
#define LOG_FATAL(...) \
  Logging::Log(__FILE__, __LINE__, __func__, LogLevel::FATAL, LoggingSubsystem::NONE, NO_ENTITY_GIVEN, __VA_ARGS__)

/*
 * Log a message about a situation that will definitely lead to degraded performance and should be addressed. (Respects
 * overrides: file name, function name)
 */
#define LOG_ERROR(...) \
  Logging::Log(__FILE__, __LINE__, __func__, LogLevel::ERROR, LoggingSubsystem::NONE, NO_ENTITY_GIVEN, __VA_ARGS__)

/*
 * Log a message about a situation that might lead to degraded performance. (Respects overrides: file name, function
 * name)
 */
#define LOG_WARN(...) \
  Logging::Log(__FILE__, __LINE__, __func__, LogLevel::WARN, LoggingSubsystem::NONE, NO_ENTITY_GIVEN, __VA_ARGS__)

/*
 * Log a general message. (Respects overrides: file name, function name)
 */
#define LOG_INFO(...) \
  Logging::Log(__FILE__, __LINE__, __func__, LogLevel::INFO, LoggingSubsystem::NONE, NO_ENTITY_GIVEN, __VA_ARGS__)

/*
 * Log a verbose message. (Respects overrides: file name, function name)
 */
#define LOG_DEBUG(...) \
  Logging::Log(__FILE__, __LINE__, __func__, LogLevel::DEBUG, LoggingSubsystem::NONE, NO_ENTITY_GIVEN, __VA_ARGS__)

/*
 * Engine crash imminent. Log your last words and make your peace with the Dark Gods. (Respects overrides: entity name,
 * file name, function name)
 */
#define LOG_FATAL_ENT(entityName, ...) \
  Logging::Log(__FILE__, __LINE__, __func__, LogLevel::FATAL, LoggingSubsystem::NONE, entityName, __VA_ARGS__)

/*
 * Log a message about a situation that will definitely lead to degraded performance and should be addressed. (Respects
 * overrides: entity name, file name, function name)
 */
#define LOG_ERROR_ENT(entityName, ...) \
  Logging::Log(__FILE__, __LINE__, __func__, LogLevel::ERROR, LoggingSubsystem::NONE, entityName, __VA_ARGS__)

/*
 * Log a message about a situation that might lead to degraded performance. (Respects overrides: entity name, file name,
 * function name)
 */
#define LOG_WARN_ENT(entityName, ...) \
  Logging::Log(__FILE__, __LINE__, __func__, LogLevel::WARN, LoggingSubsystem::NONE, entityName, __VA_ARGS__)

/*
 * Log a general message. (Respects overrides: entity name, file name, function name)
 */
#define LOG_INFO_ENT(entityName, ...) \
  Logging::Log(__FILE__, __LINE__, __func__, LogLevel::INFO, LoggingSubsystem::NONE, entityName, __VA_ARGS__)

/*
 * Log a verbose message. (Respects overrides: entity name, file name, function name)
 */
#define LOG_DEBUG_ENT(entityName, ...) \
  Logging::Log(__FILE__, __LINE__, __func__, LogLevel::DEBUG, LoggingSubsystem::NONE, entityName, __VA_ARGS__)

/*
 * Engine crash imminent. Log your last words and make your peace with the Dark Gods. (Respects overrides: subsystem
 * name, file name, function name).
 */
#define LOG_FATAL_SYS(subsystem, ...) \
  Logging::Log(__FILE__, __LINE__, __func__, LogLevel::FATAL, subsystem, NO_ENTITY_GIVEN, __VA_ARGS__)

/*
 * Log a message about a situation that will definitely lead to degraded performance and should be addressed. (Respects
 * overrides: subsystem name, file name, function name).
 */
#define LOG_ERROR_SYS(subsystem, ...) \
  Logging::Log(__FILE__, __LINE__, __func__, LogLevel::ERROR, subsystem, NO_ENTITY_GIVEN, __VA_ARGS__)

/*
 * Log a message about a situation that might lead to degraded performance. (Respects overrides: subsystem name, file
 * name, function name).
 */
#define LOG_WARN_SYS(subsystem, ...) \
  Logging::Log(__FILE__, __LINE__, __func__, LogLevel::WARN, subsystem, NO_ENTITY_GIVEN, __VA_ARGS__)

/*
 * Log a general message. (Respects overrides: subsystem name, file name, function name).
 */
#define LOG_INFO_SYS(subsystem, ...) \
  Logging::Log(__FILE__, __LINE__, __func__, LogLevel::INFO, subsystem, NO_ENTITY_GIVEN, __VA_ARGS__)

/*
 * Log a verbose message. (Respects overrides: subsystem name, file name, function name).
 */
#define LOG_DEBUG_SYS(subsystem, ...) \
  Logging::Log(__FILE__, __LINE__, __func__, LogLevel::DEBUG, subsystem, NO_ENTITY_GIVEN, __VA_ARGS__)

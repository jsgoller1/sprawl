#pragma once

#include <cassert>

#include "Logging.hh"

#ifdef WRONG_ASSUMPTIONS_FATAL
/*
 * Crashes the engine if `predicate` is false. Use this to square up, thot. 😤
 */
#define ASSUMPTION(predicate, message) \
  (void)message;                       \
  assert(predicate);
#else
/*
 * Logs `message` at LogLevel::ERROR if `predicate` is false; use this to explicitly confirm assumptions you are relying
 * on for correct behavior.
 */
#define ASSUMPTION(predicate, message)                                                                      \
  Logging::Log(LOGGING_METAINFO, ((predicate) ? LogLevel::DEBUG : LogLevel::ERROR), LoggingSubsystem::NONE, \
               NO_ENTITY_GIVEN, "ASSUMPTION: {0} - {1}", message, ((predicate) ? "True" : "False"));
#endif

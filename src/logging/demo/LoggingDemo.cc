#include "Logging.hh"

using namespace Logging;

static void attack() { LOG_DEBUG("This message was allowed due to a function-level override."); }

int main() {
  // Basics
  setDefaultLogLevel(DEBUG);
  LOG_DEBUG("Noisy {0} you need for {1}.", "information", "debugging");
  LOG_INFO("This is a general message.");
  LOG_WARN("...did something bad happen?");
  LOG_ERROR("Ok, something bad happened.");
  LOG_FATAL("WE'RE ALL GOING TO DIE.");

  // Logging per system or entity
  LOG_FATAL_SYS(RENDERING, "The renderer failed catastrophically.");
  LOG_DEBUG_ENT("Player", "Moved to ({0}, {1})", 500, 600);
  LOG_WARN_ENT("Archer", "targeted an ally in {0}; the AI system should prevent this!", "TOWER_2");

  // Overrides
  setDefaultLogLevel(ERROR);
  setOverrideSubsystem(PHYSICS, DEBUG);
  setOverrideFunc("attack", DEBUG);
  setOverrideEntity("Player", DEBUG);
  LOG_DEBUG_SYS(RENDERING, "This message was suppressed; it will not appear in the output");
  LOG_DEBUG_SYS(PHYSICS, "This message was allowed because of a subsystem-level override.");
  LOG_DEBUG_ENT("Player", "This message was allowed due to an entity-level override.");
  attack();
  setOverrideFile("src/logging/demo/LoggingDemo.cc", DEBUG);
  LOG_DEBUG("This message was allowed due to a file-level override.");

  // Modify display settings
  setShowTime(false);
  setShowSubsystemName(false);
  setShowFile(false);
  LOG_ERROR("This message has some of the display header missing.");
  setShowTime(true);
  setShowSubsystemName(true);
  setShowFile(true);
  setColorUse(false);
  LOG_ERROR("This message doesn't use colors.");

  return 0;
}

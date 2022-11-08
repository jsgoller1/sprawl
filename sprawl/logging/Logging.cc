#include "Logging.hh"

#include <map>

static std::string getLoggingTime() {
  // This function is originally from rxi/log.c
  time_t t = time(nullptr);
  struct tm* lt = localtime(&t);
  char buf[16];
  buf[strftime(buf, sizeof(buf), "%H:%M:%S", lt)] = '\0';
  return std::string(buf);
}

static fmt::v9::text_style getLevelColor(const LogLevel& level) {
  switch (level) {
    case FATAL:
      return fg(fmt::color::crimson) | fmt::emphasis::bold;
    case ERROR:
      return fg(fmt::color::red);
    case WARN:
      return fg(fmt::color::orange);
    case INFO:
      return fg(fmt::color::dark_cyan);
    case DEBUG:
      return fg(fmt::color::dark_gray);
  }
}

void Logging::impl_Log(const std::string& fileName, const int lineNo, const std::string& funcName,
                       const LogLevel& level, const LoggingSubsystem subsystem, const std::string& entityName,
                       const std::string& format, fmt::format_args& fargs) {
  if (!shouldLoggingOccur(level, funcName, fileName, entityName, subsystem)) {
    return;
  }

  std::string outputHeader = std::string("");
  if (getShowTime()) {
    outputHeader += getLoggingTime();
  }
  if (getShowLogLevel()) {
    outputHeader += fmt::format(" ({})", getName(level));
  }
  if (getShowSubsystemName() && subsystem != LoggingSubsystem::NONE) {
    outputHeader += fmt::format(" [{}]", getName(subsystem));
  }
  if (getShowEntityName() && entityName != NO_ENTITY_GIVEN) {
    outputHeader += fmt::format(" [{}]", entityName);
  }
  if (getShowFile()) {
    outputHeader += fmt::format(" {0}:{1}", fileName, lineNo);
  }
  if (getShowFuncName()) {
    outputHeader += fmt::format(" in {}()", funcName);
  }

  if (getColorUse()) {
    fmt::print(stderr, getLevelColor(level), "{0} ", outputHeader);
  } else {
    fmt::print(stderr, "{0} ", outputHeader);
  }
  fmt::vprint(stderr, format, fargs);
  fmt::print(stderr, "\n");
}

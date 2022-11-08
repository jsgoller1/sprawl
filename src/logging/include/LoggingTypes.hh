#define TEXT_COLOR_BEGIN "\x1b["
#define TEXT_COLOR_END "\x1b[0m"
#define TEXT_COLOR_BOLD_RED "1;31m"
#define TEXT_COLOR_RED "31m"
#define TEXT_COLOR_BOLD_YELLOW "1;33m"
#define TEXT_COLOR_GREEN "36m"
#define TEXT_COLOR_BLUE "32m"
#define TEXT_COLOR_LIGHT_BLUE "94m"
#define TEXT_COLOR_PINK "35m"
#define TEXT_COLOR_BROWN "33m"

enum LoggingSubsystem {
  NONE,
  COLLISIONS,
  INPUT,
  LOGGING,
  MATH,
  PHYSICS,
  RENDERING,
  SDL,
  WADLOADER,
  WORLD,
  ZONE,
};

enum LogLevel { FATAL = 4, ERROR = 3, WARN = 2, INFO = 1, DEBUG = 0 };

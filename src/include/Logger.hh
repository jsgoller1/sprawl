
#include "Types.hh"

#define SDL_ERROR_OCCURRED -1

// TODO: rename; this collides with an existing log()
void log(const string& message);
void logSDLError(int sdlErrorCode, const string& callerFnName);

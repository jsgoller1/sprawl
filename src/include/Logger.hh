#include "Types.hh"

#define SDL_ERROR_OCCURRED -1

void log(const string& message);
void logSDLError(int sdlErrorCode, const string& callerFnName);

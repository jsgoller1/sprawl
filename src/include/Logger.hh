#include <iostream>
#include <string>

#define SDL_ERROR_OCCURRED -1

using std::string;
using std::to_string;

void log(const string& message);
void logSDLError(int sdlErrorCode, const string& callerFnName);

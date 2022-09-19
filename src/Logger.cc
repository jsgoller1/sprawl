#include "Logger.hh"

#include <SDL2/SDL.h>

void log(const string& message) { printf("%s\n", message.c_str()); }

/*
TODO: Clang will eventually support the <source_location> C++20 experimental
feature which will allow us to get useful debugging information via:
```c++
  char* fileName = (char*)location.file_name();
  int lineNo = location.line();
  int columnNo = location.column();
  char* functionName = (char*)location.function_name();
  printf("file: %s(%d:%d) `%s`:\n", fileName, lineNo, columnNo, functionName);
```
For now though, switching compilers is too much work for so we'll just do a dumb
"pass the name of the caller by hand" approach. Should be merged any day now and
be supported in llvm 15. See https://github.com/llvm/llvm-project/issues/56363
and https://reviews.llvm.org/D120634.
*/

void logSDLError(int sdlErrorCode, const string& callerFnName) {
  if (sdlErrorCode) {
    printf("%s: %s\n", callerFnName.c_str(), SDL_GetError());
  }
  SDL_ClearError();
}

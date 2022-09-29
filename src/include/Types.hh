#pragma once

#include <SDL2/SDL.h>

#include <string>

#include "Memory.hh"

typedef std::string FilePath;
typedef shared_ptr<FilePath> FilePathSPtr;
typedef std::string GameObjectName;
typedef shared_ptr<GameObjectName> GameObjectNameSPtr;

typedef double real;
typedef real PositionUnit;
typedef PositionUnit YCoord;
typedef PositionUnit XCoord;
typedef unsigned long long time_ms;
typedef real time_ms_float;
/*
 * Per policy in Math.hh, we use reals / floating point numbers everywhere
 * possible. Anytime we use an int (either because we have to or we could use a
 * float but shouldn't: array index, return codes, timestamps, birth month,
 * etc), we define a new type to be explicitly used for that purpose. Enums are
 * preferable to typedefs but not always possible.
 */
typedef int arrayIndex;

/*
enum ReturnCode {
  ZERO = 0,
};

enum BitFlags {
  ZERO = 0,
};
*/

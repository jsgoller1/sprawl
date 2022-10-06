#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <algorithm>
#include <cfloat>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "Memory.hh"

using std::set;
using std::string;
using std::to_string;
using std::vector;

typedef std::string FilePath;
typedef std::string GameObjectID;

typedef double real;
typedef real PositionUnit;
typedef PositionUnit ScreenWidth;
typedef PositionUnit ScreenHeight;
typedef PositionUnit YCoord;
typedef PositionUnit XCoord;
typedef real time_ms;
typedef real time_s;
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

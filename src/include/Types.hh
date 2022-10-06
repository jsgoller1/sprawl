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

using std::pair;
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

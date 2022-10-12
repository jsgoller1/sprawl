#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <algorithm>
#include <cfloat>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "Memory.hh"

// TODO: Move these to WAD
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SCREEN_X_CENTER (PositionUnit)(1920 / 2)
#define SCREEN_Y_CENTER (PositionUnit)(1080 / 2)

using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::set;
using std::string;
using std::to_string;
using std::vector;

typedef string FilePath;
typedef string EntityName;

typedef double real;
typedef real PositionUnit;
typedef PositionUnit ScreenWidth;
typedef PositionUnit ScreenHeight;
typedef PositionUnit YCoord;
typedef PositionUnit XCoord;
typedef real time_ms;
typedef real time_s;

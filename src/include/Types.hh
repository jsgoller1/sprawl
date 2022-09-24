#pragma once

#include <SDL2/SDL.h>

#include <string>

#include "Memory.hh"

typedef double real;
typedef real PositionUnit;
typedef PositionUnit YCoord;
typedef PositionUnit XCoord;
typedef std::string FilePath;
typedef shared_ptr<FilePath> FilePathSPtr;
typedef std::string GameObjectName;
typedef shared_ptr<GameObjectName> GameObjectNameSPtr;

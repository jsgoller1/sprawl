#pragma once

#include <SDL2/SDL.h>

#include <string>

#include "Memory.hh"

typedef std::string FilePath;
typedef shared_ptr<FilePath> FilePathSPtr;
typedef std::string CharacterName;
typedef shared_ptr<CharacterName> CharacterNameSPtr;
typedef shared_ptr<SDL_Point> PointSPtr;

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <algorithm>
#include <cassert>
#include <cfloat>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include "Memory.hh"

#define TEXT_COLOR_BEGIN "\x1b["
#define TEXT_COLOR_END "\x1b[0m"
#define TEXT_COLOR_BOLD_RED "1;31m"
#define TEXT_COLOR_RED "31m"
#define TEXT_COLOR_BOLD_YELLOW "1;33m"
#define TEXT_COLOR_GREEN "36m"
#define TEXT_COLOR_BLUE "32m"
#define TEXT_COLOR_LIGHT_BLUE "94m"
#define TEXT_COLOR_PINK "35m"
#define TEXT_COLOR_BROWN "33m"

using std::cout;
using std::endl;
using std::get;
using std::map;
using std::pair;
using std::reference_wrapper;
using std::set;
using std::string;
using std::to_string;
using std::tuple;
using std::vector;

typedef string FilePath;
typedef string EntityName;

struct NotImplementedException : std::exception {
  const char* what() const noexcept override { return "Not implemented yet!\n"; }
};

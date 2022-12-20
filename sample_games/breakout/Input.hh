#pragma once
#include "Vect2D.hh"

typedef struct Input {
  Vect2D mousePos = Vect2D{.x = 0, .y = 0};
  bool shouldQuit = false;
} Input;

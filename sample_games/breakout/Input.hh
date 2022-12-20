#pragma once
#include "Vect2D.hh"

typedef struct Input {
  Vect2D mousePos = Vect2D(0, 0);
  bool shouldQuit = false;
  bool buttonPressed = false;
} Input;

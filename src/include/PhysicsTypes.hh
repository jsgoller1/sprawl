#pragma once
#include "PositionTypes.hh"

typedef PositionUnit Magnitude;

typedef struct Force {
  Direction direction;
  Magnitude magnitude;
} Force;

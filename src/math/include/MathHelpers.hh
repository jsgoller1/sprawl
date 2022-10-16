#pragma once

#include "Box.hh"
#include "Memory.hh"
#include "Real.hh"
#include "Vect2D.hh"

#define MAX(x, y) ((x < y) ? y : x)
#define MIN(x, y) ((x > y) ? y : x)

bool intervalsOverlap(const PositionUnit low1, const PositionUnit hi1,
                      const PositionUnit low2, const PositionUnit hi2);

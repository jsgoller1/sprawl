#pragma once

#include "Direction.hh"
#include "Line.hh"
#include "Real.hh"
#include "Vect2D.hh"

#define MAX(x, y) ((x < y) ? y : x)
#define MIN(x, y) ((x > y) ? y : x)

enum PointOrientation { COLINEAR = 0, CLOCKWISE = 1, COUNTERCLOCKWISE = 2 };

bool rangeContainsVal(const real a, const real b, const real val);

bool intervalsOverlap(const PositionUnit low1, const PositionUnit hi1,
                      const PositionUnit low2, const PositionUnit hi2);

PointOrientation getOrientation(const Vect2D& p1, const Vect2D& p2,
                                const Vect2D& p3);

Vect2D toVect2D(const Direction& dir);
Direction toDirection(const Vect2D& vect);

Vect2D closest(const Vect2D& origin, const Vect2D& vect1, const Vect2D& vect2);

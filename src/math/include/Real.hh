#pragma once

/*
 * NOTE: I wanted to avoid using floating point operations anywhere, because I
 * don't want to deal with:
 * - Precision issues and comparison
 * - Casting from integral to floating point correctly and vice versa
 * - Convering to int screen coordinates for SDL.
 * As an aside, the DOOM engine was implemented entirely with integer operations
 * (DOOM Game Engine Black Book, p.48) and smoothly did nearly everything we'll
 * want to do. If necessary, we can go down the FP rabbit hole later on.
 *
 * That being said, our current physics implementation uses drag coefficients
 * which need to support multiplication / addition / etc; we could do this by
 * implementing a fraction type with numerators and denominators, but I feel
 * like that's overengineering.
 *
 * So here's the strategy moving forward:
 * - We don't have a performance problem that requires attention until we have
 * an actual performance problem.
 * - Everything is a real number / double unless otherwise stated.
 * - Real number comparisons must use the below functions. We cannot
 * programmatically enforce this unless we implement real as a class, which
 * feels like overkill.
 * - If something _isn't_ a real (e.g. arr index) or can be more simply handled
 * as an integer (time_ms), it gets its own type via a class def or typedef. No
 * 'naked ints' or inline int values. The idea here is to make types more
 * explicit and catch accidental conversion as easily as possible.
 * - Conversion of reals to ints for SDL's sake (screen coordinates, texture
 * sizes, etc) must happen as close to the SDL boundary as possible.
 */

typedef double real;
typedef real PositionUnit;
typedef PositionUnit ScreenWidth;
typedef PositionUnit ScreenHeight;
typedef PositionUnit YCoord;
typedef PositionUnit XCoord;
typedef real time_ms;
typedef real time_s;

#define FLOAT_EQ_ACCEPTABLE_MARGIN_OF_ERROR 0.00000001
bool eq(const real& real1, const real& real2);
bool lt(const real& real1, const real& real2);
bool gt(const real& real1, const real& real2);
bool neq(const real& real1, const real& real2);
bool lte(const real& real1, const real& real2);
bool gte(const real& real1, const real& real2);

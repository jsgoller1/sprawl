#include "Math.hh"
#include "Memory.hh"
#include "PhysicsTypes.hh"
#include "Time.hh"
#include "Types.hh"

Vect2D calculateAcceleration(const Vect2D& netForce, const real mass);
Vect2D calculateVelocity(const time_ms duration, const Vect2D& acceleration);
Vect2D calculateDragForce(const Vect2D& velocity, const real dragCoeff);
string CollisionAxisToString(const CollisionAxis axis);

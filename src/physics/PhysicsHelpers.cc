#include "PhysicsHelpers.hh"

Vect2D calculateAcceleration(const Vect2D& netForce, const real mass) {
  Vect2D newAcceleration = Vect2D::zero();
  newAcceleration.addScaledVector(netForce, (1.0 / mass));
  return newAcceleration;
}
Vect2D calculateVelocity(const time_ms duration, const Vect2D& acceleration) {
  Vect2D newVelocity = Vect2D::zero();
  newVelocity.addScaledVector(acceleration, duration);
  return newVelocity;
}

Vect2D calculateDragForce(const Vect2D& velocity, const real dragCoeff) {
  // NOTE: We use a hack for calculating drag; actual drag is F = 1/2 * v^2 *
  // dragCoeff (we can ignore fluid density/surface area) See:
  // https://en.wikipedia.org/wiki/Drag_(physics)#The_drag_equation
  Vect2D dragForce = Vect2D(velocity);
  dragForce.invert();
  dragForce *= dragCoeff;
  return dragForce;
}

string CollisionAxisToString(const CollisionAxis axis) {
  switch (axis) {
    case X_AND_Y:
      return string("X_AND_Y");
    case Y_ONLY:
      return string("Y_ONLY");
    case X_ONLY:
      return string("X_ONLY");
    case X_OR_Y:
      return string("X_OR_Y");
  }
}

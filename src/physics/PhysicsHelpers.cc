#include "PhysicsHelpers.hh"

shared_ptr<Vect2D> calculateAcceleration(const time_ms duration,
                                         const shared_ptr<Vect2D> netForce,
                                         const real mass) {
  shared_ptr<Vect2D> newAcceleration = Vect2D::zero();
  newAcceleration->addScaledVector(*(netForce), (1.0 / mass));
  return newAcceleration;
}
shared_ptr<Vect2D> calculateVelocity(const time_ms duration,
                                     const shared_ptr<Vect2D> acceleration) {
  shared_ptr<Vect2D> newVelocity = Vect2D::zero();
  newVelocity->addScaledVector(acceleration, duration);
  return newVelocity;
}

shared_ptr<Vect2D> calculateDragForce(const shared_ptr<Vect2D> velocity,
                                      const real dragCoeff) {
  // NOTE: We use a hack for calculating drag; actual drag is F = 1/2 * v^2 *
  // dragCoeff (we can ignore fluid density/surface area) See:
  // https://en.wikipedia.org/wiki/Drag_(physics)#The_drag_equation
  shared_ptr<Vect2D> dragForce = shared_ptr<Vect2D>(velocity);
  dragForce->invert();
  (*dragForce) *= (real(1.0) - dragCoeff);
  return dragForce;
}

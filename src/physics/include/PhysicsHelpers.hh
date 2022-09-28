#include "Math.hh"
#include "Memory.hh"
#include "Time.hh"
#include "Types.hh"

shared_ptr<Vect2D> calculateAcceleration(const time_ms duration,
                                         const shared_ptr<Vect2D> netForce,
                                         const real mass);
shared_ptr<Vect2D> calculateVelocity(const time_ms duration,
                                     const shared_ptr<Vect2D> acceleration);
shared_ptr<Vect2D> calculateDragForce(const shared_ptr<Vect2D> velocity,
                                      const real dragCoeff);

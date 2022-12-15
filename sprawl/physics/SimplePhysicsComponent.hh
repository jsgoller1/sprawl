#include "Collision.hh"
#include "PhysicsComponent.hh"

class SimplePhysicsComponent : public PhysicsComponent {
 public:
  SimplePhysicsComponent(const std::shared_ptr<Identity> ownerIdentity = nullptr, const PositionUnit maxSpeed = 0.0,
                         const PositionUnit minSpeed = 0.0, const Vect2D velocity = Vect2D::zero());
  ~SimplePhysicsComponent() override;

  void resolveCollision(const Collision& collision) override;
  Vect2D integrate(const time_ms duration) override;
};

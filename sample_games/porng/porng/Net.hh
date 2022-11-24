#pragma once

#include "GameObject.hh"

class Net : public GameObject {
 public:
  Net(const EntityName entityName, const std::shared_ptr<PositionComponent> positionComponent = nullptr,
      const std::shared_ptr<DrawingComponent> drawingComponent = nullptr);
  ~Net() override;

  // TODO: This technique of reconciling smart pointers with the covariant return rule wound up being an anti-pattern
  // and is slated for removal. It's here at present merely to satisfy concretizing this class, but won't do anything.
  // std::shared_ptr<PhysicsComponent> getPhysicsComponent() const;
  // void setPhysicsComponent(const std::shared_ptr<PhysicsComponent> physicsComponent);

 private:
  std::shared_ptr<PositionComponent> positionComponent;
  std::shared_ptr<DrawingComponent> drawingComponent;

  // TODO: This technique of reconciling smart pointers with the covariant return rule wound up being an anti-pattern
  // and is slated for removal. It's here at present merely to satisfy concretizing this class, but won't do anything.
  // void setPhysicsComponent_impl(PhysicsComponent* const comp) override;
  // PhysicsComponent* getPhysicsComponent_impl() const override;
};

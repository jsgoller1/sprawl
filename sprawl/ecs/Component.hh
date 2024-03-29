#pragma once

#include <memory>

#include "Entity.hh"

// fwd decls
class Actor;

constexpr bool COMPONENT_ENABLED = true;

class Component : public Entity {
  /*
   * Components are modules of specialized behavior that can be composed into actors. The engine creates subclasses of
   * Component that are associated with behavior requiring engine systems (managers) to function, such as
   * PhysicsComponent or CollisionComponent. All components register their owners with their respective manager on
   * creation, and deregister on deletion.
   */

 public:
  virtual std::string toString() const override;

  std::shared_ptr<Actor> getOwner() const;
  void setOwner(const std::shared_ptr<Actor> owner);

  bool isEnabled() const;
  void setEnabled(const bool setting);

  virtual void managerRegister() = 0;
  virtual void managerUnregister() = 0;

  virtual ~Component() override = default;

 protected:
  Component(const bool enabled = COMPONENT_ENABLED);

 private:
  std::shared_ptr<Actor> owner;
  bool enabled;
};

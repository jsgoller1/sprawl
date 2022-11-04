#pragma once

#include "EntityManager.hh"
#include "Logging.hh"
#include "Types.hh"

// Forward decl
class PhysicsComponent;

class Entity {
  /*
   * An Entity is anything that exists in the game world and makes use of
   * components. Every Entity must have a unique Identity. Entities may also
   * have names, but are not required to.
   */

 public:
  shared_ptr<Identity> getIdentity() const;
  EntityName getName() const;
  void setName(const EntityName name);

 protected:
  Entity(const EntityName name);
  ~Entity();

 private:
  shared_ptr<Identity> _identity;
  EntityName _name;
};

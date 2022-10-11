#pragma once

#include "EntityManager.hh"
#include "Types.hh"
#include "Zone.hh"

typedef string EntityName;

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
  shared_ptr<EntityName> getName() const;
  void setName(const shared_ptr<EntityName> name);

 protected:
  Entity(const shared_ptr<EntityName> name = nullptr);
  ~Entity();

 private:
  shared_ptr<Identity> identity;
  shared_ptr<EntityName> entityName;
};

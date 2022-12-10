#pragma once

#include "Logging.hh"
#include "Types.hh"

// Forward decl
class PhysicsComponent;
class Identity;

class Entity : public std::enable_shared_from_this<Entity> {
  /*
   * An Entity is anything that exists in the game world and makes use of
   * components. Every Entity must have a unique Identity. Entities may also
   * have names, but are not required to.
   */

 public:
  Identity& getIdentity() const;
  EntityName getName() const;
  void setName(const EntityName name);

 protected:
  Entity(const EntityName name);
  ~Entity();

 private:
  std::shared_ptr<Identity> _identity = nullptr;
  EntityName _name = "";
};

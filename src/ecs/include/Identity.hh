#pragma once
#include "ECSTypes.hh"
#include "Memory.hh"

/*
 * An Identity is a unique data object that can answer questions about "who this
 * object is", or if two objects are the same (how this is determined is opaque
 * to the owner of an Identity). Identity should not be used to store any other
 * global state about an object. An Identity can only be created by the global
 * singleton IdentityManager.
 */

// Forward decls
class EntityManager;

class Identity {
  shared_ptr<const EntityID> getId() const { return this->id; }
  shared_ptr<const EntityName> getName() const { return this->name; }
  bool operator==(const Identity& id) const;

 private:
  friend EntityManager;
  explicit Identity();
  explicit Identity(shared_ptr<const EntityID> id,
                    shared_ptr<const EntityName> name)
      : id(id), name(name){};
  shared_ptr<const EntityID> id;
  shared_ptr<const EntityName> name;
};

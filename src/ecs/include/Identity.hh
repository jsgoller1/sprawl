#pragma once
#include <string>

/*
 * An Identity is a unique data object that can answer questions about "who this
 * object is", or if two objects are the same (how this is determined is opaque
 * to the owner of an Identity). Identity should not be used to store any other
 * global state about an object. An Identity can only be created by the global
 * singleton IdentityManager.
 */

#include "Memory.hh"

using std::string;
// EntityID is a unique identifier for an Identity, determined
// by IdentityManager; it cannot be modified or generated by users
// of the Identity.
typedef string EntityID;

// EntityName is a string-like object that users of Identity can construct
// from strings, and allows them to name Identities.
typedef string EntityName;

// Forward decl for friend declaration, see IndentityManager.hh
class IdentityManager;
class Identity {
  shared_ptr<const EntityID> getId() const { return this->id; }
  shared_ptr<const EntityName> getName() const { return this->name; }
  bool operator==(const Identity& id) const;

 private:
  friend IdentityManager;
  explicit Identity();
  explicit Identity(shared_ptr<const EntityID> id,
                    shared_ptr<const EntityName> name)
      : id(id), name(name){};
  shared_ptr<const EntityID> id;
  shared_ptr<const EntityName> name;
};
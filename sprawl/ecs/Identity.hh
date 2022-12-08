#pragma once

#include <memory>
#include <string>

#include "Types.hh"

typedef std::string EntityID;

const EntityID NullIdentity = EntityID("NullIdentity");

class Identity : public std::enable_shared_from_this<Identity> {
 public:
  const EntityID& getEntityID() const;
  std::string toString();

  static Identity null() { return Identity(NullIdentity); }

 private:
  friend class EntityManager;
  Identity(const EntityID& entityID);

  EntityID _entityID;
};

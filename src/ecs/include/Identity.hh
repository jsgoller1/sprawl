#pragma once
#include "Types.hh"

typedef std::string EntityID;

class Identity {
 public:
  shared_ptr<const EntityID> getEntityID() const;
  string toString();

 private:
  friend class EntityManager;
  Identity(const shared_ptr<EntityID> entityID);

  shared_ptr<const EntityID> entityID;
};

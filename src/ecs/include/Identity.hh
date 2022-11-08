#pragma once

#include <memory>
#include <string>

#include "Types.hh"

typedef std::string EntityID;

class Identity {
 public:
  std::shared_ptr<const EntityID> getEntityID() const;
  std::string toString();

 private:
  friend class EntityManager;
  Identity(const std::shared_ptr<EntityID> entityID);

  std::shared_ptr<const EntityID> entityID;
};

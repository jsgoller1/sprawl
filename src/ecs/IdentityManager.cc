#include "IdentityManager.hh"

shared_ptr<const Identity> IdentityManager::getNewIdentity(const string& name) {
  shared_ptr<const EntityID> entityId = shared_ptr<EntityID>(
      new EntityID("identity-" + std::to_string(this->entityCount++)));
  shared_ptr<const EntityName> entityName =
      shared_ptr<const EntityName>(new EntityName(name));
  return shared_ptr<const Identity>(new Identity(entityId, entityName));
}

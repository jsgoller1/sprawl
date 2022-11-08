#pragma once

#include <map>
#include <set>
#include <string>

#include "Identity.hh"
#include "Types.hh"

// Forward decl
class Entity;

class EntityManager {
  /*
   * EntityManager is a singleton class who keeps
   * track of existing objects derived from Entity and their Identity.
   */

 public:
  static std::shared_ptr<EntityManager> instance() {
    // Static variable initialization only occurs once, so
    // if instance() is called and this->instance is already
    // initialized, it won't be initialized again.
    // See this spec, section 6.7.4:
    // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2010/n3092.pdf
    static std::shared_ptr<EntityManager> instance = std::shared_ptr<EntityManager>(new EntityManager());
    return instance;
  }
  std::shared_ptr<Identity> getIdentity(Entity* entity) const;
  Entity* getEntity(const std::shared_ptr<Identity> identity) const;

  std::shared_ptr<std::set<Entity*>> getAllEntities();
  std::shared_ptr<std::set<std::shared_ptr<Identity>>> getAllIdentities();

 private:
  // Only Entity should be allowed to call Manage() / Unmanage() as part of its
  // construction and destruction per RAII
  friend class Entity;
  std::shared_ptr<Identity> manage(Entity* entity, const EntityName& = nullptr);
  void unmanage(Entity* entity);

  // Make default constructor private and delete copy/move so extra instances
  // can't be created/moved.
  EntityManager();
  EntityManager(const EntityManager&) = delete;
  EntityManager& operator=(const EntityManager&) = delete;
  EntityManager(EntityManager&&) = delete;
  EntityManager& operator=(EntityManager&&) = delete;

  std::shared_ptr<Identity> createIdentity(const EntityName name);
  unsigned long long entityCount = 0;

  // NOTE: EntityManager's main responsibility is over the relationship between
  // entities and identities; this relationship is bijective (there is exactly
  // one identity for exactly one entity, and vice versa); we do this by storing
  // two maps of the same keys and values, but one is reversed. This obviously
  // requires twice as much storage but we get O(c) lookups in return. Anytime
  // one map is updated, the other must be as well.
  // TODO: We should probably refactor this functionality to a different class
  // and just compose it into EntityManager.
  std::shared_ptr<std::map<std::shared_ptr<Identity>, Entity*>> identityToEntity;
  std::shared_ptr<std::map<Entity*, std::shared_ptr<Identity>>> entityToIdentity;
};

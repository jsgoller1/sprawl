
#pragma once

#include "Identity.hh"
#include "Memory.hh"

/*
 * EntityManager is a singleton class whose sole responsibility is to keep
 * track of Entity objects, which represent things that exist in the game world
 * (some of which are interactive, i.e. GameObjects, while others are not, i.e.
 * Backgrounds). The EntityManager has the following responsibilities:
 * - Ensure Entities have unique Identity.
 * - Providing a read-only mapping of Identities to the Entities that own them
 * via a public interface.
 *
 * Only the EntityManager is allowed to set an object's identity, and how it
 * does so is opaque to all other systems.
 *
 * Eventually, the EntityManager will be (probably) responsible for informing
 * Entities about Managers and vice versa during Entity creation and
 * destruction, but this isn't needed right now since we have so few Managers.
 * Once we actually have several manager classes and respective component types,
 * we'll want to refactor them to generic Manager and Component base classes,
 * and have EntityManager coordinate between them.
 *
 */

// Forward decls
class Entity;

class EntityManager {
 public:
  static shared_ptr<EntityManager> instance() {
    // Static variable initialization only occurs once, so
    // if instance() is called and this->instance is already
    // initialized, it won't be initialized again.
    // See this spec, section 6.7.4:
    // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2010/n3092.pdf
    static shared_ptr<EntityManager> instance =
        shared_ptr<EntityManager>(new EntityManager());
    return instance;
  }
  shared_ptr<Entity> getEntity(const shared_ptr<Identity> identity);

 private:
  // Default constructor is private so EntityManager can only be instantiated
  // via instance()
  EntityManager();

  // Delete copy/move constructors so extra instances can't be created.
  EntityManager(const EntityManager&) = delete;
  EntityManager& operator=(const EntityManager&) = delete;
  EntityManager(EntityManager&&) = delete;
  EntityManager& operator=(EntityManager&&) = delete;

  shared_ptr<map<shared_ptr<const Identity>, shared_ptr<Entity>>> entityMap;
  unsigned long long entityCount;

  friend Entity();
  friend ~Entity();
  shared_ptr<const Identity> createIdentity(const shared_ptr<string> name);
  void destroyIdentity(const shared_ptr<const Identity> name);
};

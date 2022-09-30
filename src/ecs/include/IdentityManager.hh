#pragma once
#include <string>

#include "Identity.hh"
#include "Memory.hh"

/*
 * IdentityManager is a singleton class whose sole responsibility is to keep
 * track of Identity objects. Presently, the IdentityManager's only job is to
 * ensure Identities are unique. In the future, we may extend it to some kind of
 * management / game object registry system.
 */

class IdentityManager {
 public:
  static shared_ptr<IdentityManager> instance() {
    // Static variable initialization only occurs once, so
    // if instance() is called and this->instance is already
    // initialized, it won't be initialized again.
    // See this spec, section 6.7.4:
    // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2010/n3092.pdf
    static shared_ptr<IdentityManager> instance =
        shared_ptr<IdentityManager>(new IdentityManager());
    return instance;
  }
  shared_ptr<const Identity> getNewIdentity(const string& name);
  shared_ptr<const Identity> getNewIdentity(const shared_ptr<string> name) {
    return this->getNewIdentity(*name);
  }

 private:
  IdentityManager() { this->entityCount = 0; };

  // Delete copy/move so extra instances can't be created/moved.
  IdentityManager(const IdentityManager&) = delete;
  IdentityManager& operator=(const IdentityManager&) = delete;
  IdentityManager(IdentityManager&&) = delete;
  IdentityManager& operator=(IdentityManager&&) = delete;

  unsigned long long entityCount;
};

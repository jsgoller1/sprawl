#pragma once

#include "Identity.hh"
#include "IdentityManager.hh"

/*
 * An Entity is anything with an Identity that can have Components, such as
 * Background and GameObject.
 */

class Entity {
 public:
  Entity(const std::string& name);
  Entity(const shared_ptr<std::string> name) : Entity(*name) {}
  shared_ptr<const Identity> getIdentity() { return this->identity; }

 private:
  shared_ptr<const Identity> identity;
};

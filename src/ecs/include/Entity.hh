#pragma once

#include "ECSTypes.hh"
#include "Identity.hh"

/*
 * An Entity is anything with an Identity that can have Components, such as
 * Background and GameObject.
 */

class Entity {
 public:
  Entity(const std::string& name);
  Entity(const shared_ptr<std::string> name) : Entity(*name) {}
  shared_ptr<const Identity> getIdentity() const;
  ~Entity();

 private:
  shared_ptr<const Identity> identity;
};

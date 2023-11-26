#pragma once

#include "Logging.hh"
#include "Types.hh"

class Entity {
  /*
   * An Entity is anything that needs a unique identifier - presently, Actors and Components.
   */

 public:
  UUID getUUID() const;
  virtual std::string toString() const = 0;

 protected:
  Entity();
  virtual ~Entity();

 private:
  UUID uuid;
};

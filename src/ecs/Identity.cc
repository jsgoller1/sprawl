#include "Identity.hh"

bool Identity::operator==(const Identity& identity) const {
  return *this->id == *identity.getId() && *this->name == *identity.getName();
}

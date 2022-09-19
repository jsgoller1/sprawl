#include "Character.hh"

Character::Character(const CharacterName& name) {
  this->name = CharacterNameSPtr(new CharacterName(name));
}

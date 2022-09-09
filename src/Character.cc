#include "Character.hh"

Character::Character(const CharacterName& name) {
  this->name = CharacterNamePS(new CharacterName(name));
}

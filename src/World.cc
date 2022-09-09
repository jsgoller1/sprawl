#include "World.hh"

#include "GameAction.hh"
#include "Types.hh"

World::World(const FilePathPS wadDirPS) {}

World::World() {
  // TODO: Look on disk at the given path for a config file detailing where
  // zone data is stored, then begin initializing zones from data files.
  this->currentZone = ZonePS(new Zone);
  this->currentZone->loadHardcoded();
}

void World::update(const GameAction& action) {
  this->currentZone->update(action);
}
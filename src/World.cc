#include "World.hh"

#include "DrawingComp.hh"
#include "GameAction.hh"
#include "Types.hh"

using std::vector;

World::World(const FilePathSPtr wadDirSPtr) {}

World::World() {
  // TODO: Look on disk at the given path for a config file detailing where
  // zone data is stored, then begin initializing zones from data files.
  this->currentZone = ZoneSPtr(new Zone());
  this->currentZone->loadHardcoded();
}

void World::update(const GameAction& action) {
  this->currentZone->update(action);
}

DrawingCompSPtrCollectionSPtr World::getDrawables() {
  return this->currentZone->getDrawables();
}

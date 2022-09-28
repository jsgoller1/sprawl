#include "World.hh"

World::World(const shared_ptr<FilePath> wadPath) {
  shared_ptr<WADLoader> wadLoader = shared_ptr<WADLoader>(new WADLoader());
  this->currentZone = wadLoader->zoneFromWAD(wadPath);
}

void World::update(const GameAction& action, const time_ms duration) {
  this->currentZone->update(action, duration);
}

DrawingCompSPtrCollectionSPtr World::getDrawables() {
  return this->currentZone->getDrawables();
}

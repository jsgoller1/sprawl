#include "World.hh"

World::World(const shared_ptr<FilePath> wadPath) {
  shared_ptr<WADLoader> wadLoader = shared_ptr<WADLoader>(new WADLoader());
  this->currentZone = wadLoader->zoneFromWAD(wadPath);
}

#pragma once

#include "PositionComp.hh"
#include "Types.hh"
#include "Zone.hh"
#include "json.hpp"

using json = nlohmann::json;

class WADLoader {
 public:
  shared_ptr<Zone> zoneFromWAD(const shared_ptr<FilePath> wadPath) const;

 private:
  void addBackground(shared_ptr<Zone> zone, const json& backgroundJSON) const;
  void addCharacter(shared_ptr<Zone> zone, const json& characterJSON) const;
  void addPlatform(shared_ptr<Zone> zone, const json& platformJSON) const;
};

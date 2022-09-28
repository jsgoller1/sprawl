#pragma once

#include "AIMgr.hh"
#include "Background.hh"
#include "Character.hh"
#include "DrawingComp.hh"
#include "GameAction.hh"
#include "GameObject.hh"
#include "Logger.hh"
#include "Memory.hh"
#include "PhysicsMgr.hh"
#include "Platform.hh"
#include "PositionComp.hh"
#include "Texture.hh"
#include "Time.hh"
#include "Types.hh"

// Forward declaration
class WADLoader;

class Zone {
  // A Zone is a location in the World containing GameObjects
  // TODO: Initially, all zones are rectangular, have the same height as the
  // window, and every part of them should be drawn on the screen. Eventually,
  // we'll want to be able to scroll around in them

 public:
  // TODO: serialize(); // needed for saving game and level editor
  void update(const GameAction& action, const time_ms duration);
  void load(const FilePathSPtr zoneWADDirSPtr);
  void setBackground(const FilePathSPtr backgroundPath);
  DrawingCompSPtrCollectionSPtr getDrawables();
  Zone();

 private:
  // We only need to care about physics and AI going on in currentZone,
  // since only currentZone will have active GameObjects. Additionally, physics
  // might differ based on zone (underwater, outer space, cyberspace, etc)
  AIMgr aiMgr;
  shared_ptr<PhysicsMgr> physicsMgr;
  shared_ptr<GameObjectSPtrCollection> gameObjects;
  BackgroundSPtr background;
  CharacterSPtr player;

  void handleInput(const GameAction& action);
  void handlePhysics();

  friend WADLoader;
};

typedef shared_ptr<Zone> ZoneSPtr;
typedef std::vector<ZoneSPtr> ZoneSPtrCollection;

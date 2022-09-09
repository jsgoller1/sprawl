#include "AIManager.hh"
#include "GameAction.hh"
#include "GameObject.hh"
#include "Memory.hh"
#include "Types.hh"

class Zone {
  // A Zone is a location in the World containing GameObjects
  // TODO: Initially, all zones are rectangular, have the same height as the
  // window, and every part of them should be drawn on the screen. Eventually,
  // we'll want to be able to scroll around in them

 public:
  void update(const GameAction& action);
  void load(const FilePathPS zoneWADDirPS);
  void loadHardcoded();
  Zone();

 private:
  // We only need to care about physics and AI going on in currentZone,
  // since only currentZone will have active GameObjects. Additionally, physics
  // might differ based on zone (underwater, outer space, cyberspace, etc)
  AIManager aiManager;
  PhysicsManager physicsManager;
  shared_ptr<GameObjectPSCollection> gameObjects;
  // TODO: Backgrounds, once we figure out texturing
  // Background background;
};

typedef shared_ptr<Zone> ZonePS;
typedef std::vector<ZonePS> ZonePSCollection;

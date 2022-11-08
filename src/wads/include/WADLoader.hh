#pragma once
// #include <fstream>

#include "Duplication.hh"
#include "Types.hh"
#include "json.hpp"

// Forward decls;
class CollisionComponent;
class DrawingComponent;
class InputHandler;
class Identity;
class PhysicsComponent;
class PositionComponent;
class Screen;
class World;
class Zone;

using json = nlohmann::json;

template <typename KeyType>
KeyType loadKey(const json& jsonBody, const std::string& key, const KeyType& defaultVal, const LogLevel level = DEBUG) {
  if (jsonBody.contains(key)) {
    return jsonBody[key];
  }
  Logging::Log(LOGGING_METAINFO, level, WADLOADER, "",
               "Could not find key '{0}' in JSON body; using default value '{1}'", key, defaultVal);
  return defaultVal;
};

class WADLoader {
 public:
  WADLoader(const FilePath& wadPath);
  void loadLogging() const;
  std::shared_ptr<World> loadWorld() const;
  std::shared_ptr<Screen> loadScreen() const;
  std::shared_ptr<InputHandler> loadInputHandler() const;

 private:
  FilePath _wadDir;
  json _jsonBody;

  bool objectEnabled(const json& jsonBody) const;
  DuplicationBehavior handleDuplication(const json& jsonBody) const;

  std::shared_ptr<Zone> loadZone(const json& zoneData) const;
  void loadBackground(Zone& zone, const json& jsonBody) const;
  void loadCharacter(Zone& zone, const json& jsonBody) const;
  void loadPlatform(Zone& zone, const json& jsonBody) const;

  std::shared_ptr<PositionComponent> loadPositionComponent(const std::shared_ptr<Identity> ownerIdentity,
                                                           const json& jsonBody) const;
  std::shared_ptr<PhysicsComponent> loadPhysicsComponent(const std::shared_ptr<Identity> ownerIdentity,
                                                         const json& jsonBody) const;
  std::shared_ptr<DrawingComponent> loadDrawingComponent(const std::shared_ptr<Identity> ownerIdentity,
                                                         const std::shared_ptr<PositionComponent> positionComponent,
                                                         const json& jsonBody) const;
  std::shared_ptr<CollisionComponent> loadCollisionComponent(const std::shared_ptr<Identity> ownerIdentity,
                                                             const std::shared_ptr<PositionComponent> positionComponent,
                                                             const json& jsonBody) const;
};

#pragma once
// #include <fstream>

#include "Duplication.hh"
#include "Types.hh"
#include "json/json.hpp"

// Forward decls;
class Actor;
class ActorManager;
class CollisionComponent;
class CollisionManager;
class DrawingComponent;
class DrawingManager;
struct GraphicsSettings;
class InputHandler;
class PositionComponent;
class PhysicsManager;
class RealisticPhysicsComponent;
class SimplePhysicsComponent;

template <typename KeyType>
KeyType loadKey(const nlohmann::json& jsonBody, const std::string& key, const KeyType& defaultVal,
                const LogLevel level = DEBUG) {
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
  virtual ~WADLoader();
  void loadLogging() const;

  std::shared_ptr<InputHandler> loadInputHandler() const;
  GraphicsSettings loadGraphicsSettings(const nlohmann::json& jsonBody) const;

  void loadSettings(ActorManager& actorManager, CollisionManager& collisionManager, DrawingManager& drawingManager,
                    PhysicsManager& physicsManager) const;
  void loadActors(ActorManager& actorManager) const;

 private:
  void loadActor(ActorManager& actorManager, const nlohmann::json& jsonBody) const;
  void loadPositionComponent(std::shared_ptr<Actor> owner, const nlohmann::json& jsonBody) const;
  void loadRealisticPhysicsComponent(std::shared_ptr<Actor> owner, const nlohmann::json& jsonBody) const;
  void loadDrawingComponent(std::shared_ptr<Actor> owner, const nlohmann::json& jsonBody) const;
  void loadCollisionComponent(std::shared_ptr<Actor> owner, const nlohmann::json& jsonBody) const;

  bool objectEnabled(const nlohmann::json& jsonBody) const;
  DuplicationBehavior handleDuplication(const nlohmann::json& jsonBody) const;
  nlohmann::json getJsonBody() const;

  FilePath _wadDir;
  nlohmann::json _jsonBody;
};

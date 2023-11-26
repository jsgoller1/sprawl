#include "WADLoader.hh"

#include <fstream>

#include "Actor.hh"
#include "ActorManager.hh"
#include "CollisionManager.hh"
#include "Component.hh"
#include "DrawingManager.hh"
#include "GraphicsSettings.hh"
#include "Logging.hh"
#include "PhysicsManager.hh"
#include "PositionComponent.hh"

WADLoader::~WADLoader() = default;

WADLoader::WADLoader(const FilePath& wadDir) {
  std::ifstream wadFile(wadDir + "/wad.json");
  if (!wadFile.is_open()) {
    LOG_FATAL_SYS(WADLOADER, "Could not find wad.json at {0}.", wadDir);
    throw;
  }
  this->_wadDir = wadDir;
  this->_jsonBody = nlohmann::json::parse(wadFile);
}

bool WADLoader::objectEnabled(const nlohmann::json& jsonBody) const { return jsonBody.value("enabled", false); }

nlohmann::json WADLoader::getJsonBody() const { return this->_jsonBody; }

void WADLoader::loadSettings(ActorManager& actorManager, CollisionManager& collisionManager,
                             DrawingManager& drawingManager, PhysicsManager& physicsManager) const {
  (void)actorManager;
  (void)collisionManager;

  nlohmann::json jsonData = this->getJsonBody();
  drawingManager.initialize(this->loadGraphicsSettings(jsonData["graphics"]));
  if (jsonData.contains("gravityConstant")) {
    physicsManager.setGravityConstant(jsonData["gravityConstant"]);
  }
}

void WADLoader::loadActors(ActorManager& actorManager) const {
  // TODO: Add error checking with helpful messages. Pretending for now that
  // IntegrationWADLoader files are always correctly structured json
  nlohmann::json jsonData = this->getJsonBody();

  if (jsonData.contains("gameObjects")) {
    std::shared_ptr<Actor> actor;
    for (auto actorJSON : jsonData["actors"]) {
      if (actorJSON["enabled"] == false) {
        continue;
      }
      LOG_DEBUG_SYS(WADLOADER, "Loading Actor: {0}", nlohmann::to_string(actorJSON));
      this->loadActor(actorManager, actorJSON);
    }
  }
}

void WADLoader::loadActor(ActorManager& actorManager, const nlohmann::json& jsonBody) const {
  if (!this->objectEnabled(jsonBody)) {
    return;
  }

  std::shared_ptr<Actor> actor = actorManager.createActor(jsonBody["name"], jsonBody["scenes"]);
  this->loadPositionComponent(actor, jsonBody["position"]);
  this->loadDrawingComponent(actor, jsonBody["drawing"]);
  this->loadCollisionComponent(actor, jsonBody["collisions"]);
  this->loadRealisticPhysicsComponent(actor, jsonBody["physics"]);
}

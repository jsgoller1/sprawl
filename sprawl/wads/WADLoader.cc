#include "WADLoader.hh"

#include <fstream>

#include "GameObject.hh"
#include "Logging.hh"
#include "World.hh"

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

void WADLoader::loadGameObject(World& world, const nlohmann::json& jsonBody) const {
  if (!this->objectEnabled(jsonBody)) {
    return;
  }
  std::shared_ptr<PositionComponent> positionComponent = this->loadPositionComponent(jsonBody["position"]);
  // std::shared_ptr<PhysicsComponent> physicsComponent = this->loadRealisticPhysicsComponent(jsonBody["physics"]);
  std::shared_ptr<DrawingComponent> drawingComponent = this->loadDrawingComponent(jsonBody["drawing"]);
  std::shared_ptr<CollisionComponent> collisionComponent =
      this->loadCollisionComponent(jsonBody["collisions"], positionComponent);

  std::shared_ptr<GameObject> object = std::make_shared<GameObject>(
      EntityName(jsonBody.value("name", "")), positionComponent, collisionComponent, nullptr, drawingComponent);
  world.addGameObject(object);
}

bool WADLoader::objectEnabled(const nlohmann::json& jsonBody) const { return jsonBody.value("enabled", false); }

nlohmann::json WADLoader::getJsonBody() const { return this->_jsonBody; }

std::shared_ptr<World> WADLoader::loadWorld() const {
  // TODO: Add error checking with helpful messages. Pretending for now that
  // IntegrationWADLoader files are always correctly structured json

  nlohmann::json jsonData = this->getJsonBody();
  std::shared_ptr<World> world = std::make_shared<World>(this->loadGraphicsSettings(jsonData["graphics"]));

  if (jsonData.contains("gravityConstant")) {
    world->getPhysicsManager().setGravityConstant(jsonData["gravityConstant"]);
  }

  if (jsonData.contains("gameObjects")) {
    std::shared_ptr<GameObject> object;
    for (auto gameObjectJSON : jsonData["gameObjects"]) {
      if (gameObjectJSON["enabled"] == false) {
        continue;
      }
      LOG_DEBUG_SYS(WADLOADER, "Loading GameObject: {0}", nlohmann::to_string(gameObjectJSON));
      this->loadGameObject(*world, gameObjectJSON);
    }
  }

  return world;
}

#include "WADLoader.hh"

#include <fstream>

#include "Actor.hh"
#include "ActorManager.hh"
#include "BehaviorComponent.hh"
#include "BehaviorComponentFactory.hh"
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

nlohmann::json WADLoader::getJsonBody() const { return this->_jsonBody; }

void WADLoader::loadSettings(ActorManager& actorManager, BehaviorManager& behaviorManager,
                             CollisionManager& collisionManager, DrawingManager& drawingManager,
                             PhysicsManager& physicsManager) const {
  (void)actorManager;
  (void)behaviorManager;
  (void)collisionManager;

  nlohmann::json jsonData = this->getJsonBody();
  drawingManager.initialize(this->loadGraphicsSettings(jsonData["graphics"]));
  if (jsonData.contains("physics")) {
    physicsManager.setGravityConstant(jsonData["physics"]["gravityConstant"]);
  }
}

void WADLoader::loadActors(ActorManager& actorManager) const {
  // TODO: Add error checking with helpful messages. Pretending for now that
  // IntegrationWADLoader files are always correctly structured json
  nlohmann::json jsonData = this->getJsonBody();

  if (jsonData.contains("scenes")) {
    for (auto sceneJSON : jsonData["scenes"]) {
      if (sceneJSON["enabled"] == false || !sceneJSON.contains("name")) {
        continue;
      }
      if (sceneJSON.contains("actors")) {
        for (auto actorJSON : sceneJSON["actors"]) {
          if (!(actorJSON.contains("name"))) {
            continue;
          }
          LOG_DEBUG_SYS(WADLOADER, "Loading Actor: {0}", nlohmann::to_string(actorJSON));
          this->loadActor(actorManager, sceneJSON["name"], actorJSON);
        }
      }
    }
  }
}

void WADLoader::loadActor(ActorManager& actorManager, const std::string sceneID, const nlohmann::json& jsonBody) const {
  if (!JSON_OBJ_ENABLED(jsonBody)) {
    return;
  }

  std::shared_ptr<Actor> actor = actorManager.createActor(jsonBody["name"], sceneID);
  for (auto componentJSON : jsonBody["components"]) {
    if (componentJSON["enabled"] == false) {
      continue;
    }
    std::string typeName = componentJSON.value("type", "");
    if (typeName == "") {
      LOG_ERROR("No type specified for component.");
      continue;
    }
    if (typeName == "PositionComponent") {
      this->loadPositionComponent(actor, componentJSON);
    } else if (typeName == "CollisionComponent") {
      this->loadCollisionComponent(actor, componentJSON);
    } else if (typeName == "DrawingComponent") {
      this->loadDrawingComponent(actor, componentJSON);
    } else if (typeName == "PhysicsComponent") {
      this->loadRealisticPhysicsComponent(actor, componentJSON);
    } else {
      std::shared_ptr<BehaviorComponent> behaviorComponent = BehaviorComponentFactory::CreateComponent(typeName);
      if (behaviorComponent) {
        actor->addComponent(typeName, behaviorComponent);
      } else {
        LOG_ERROR("Unknown component type: {0}", typeName);
      }
    }
  }
}

#include "IntegrationWADLoader.hh"

#include <memory>
#include <string>

#include "CharacterPhysicsComponent.hh"
#include "IntegrationWorld.hh"
#include "PhysicsManager.hh"
#include "Platform.hh"

IntegrationWADLoader::~IntegrationWADLoader() = default;
IntegrationWADLoader::IntegrationWADLoader(const FilePath& wadPath) : WADLoader(wadPath) {}

std::shared_ptr<IntegrationWorld> IntegrationWADLoader::loadIntegrationWorld() const {
  // TODO: Add error checking with helpful messages. Pretending for now that
  // IntegrationWADLoader files are always correctly structured json

  nlohmann::json jsonData = this->getJsonBody();
  std::shared_ptr<IntegrationWorld> world =
      std::make_shared<IntegrationWorld>(this->loadGraphicsSettings(jsonData["graphics"]));

  if (jsonData.contains("gravityConstant")) {
    world->getPhysicsManager().setGravityConstant(jsonData["gravityConstant"]);
  }

  if (jsonData.contains("background")) {
    this->loadBackground(*world, jsonData["background"]);
  }

  if (jsonData.contains("gameObjects")) {
    std::shared_ptr<GameObject> object;
    for (auto gameObjectJSON : jsonData["gameObjects"]) {
      if (gameObjectJSON["enabled"] == false) {
        continue;
      }
      LOG_DEBUG_SYS(WADLOADER, "Loading GameObject: {0}", nlohmann::to_string(gameObjectJSON));
      if (gameObjectJSON["type"] == "Character") {
        this->loadCharacter(*world, gameObjectJSON);
      } else if (gameObjectJSON["type"] == "Platform") {
        this->loadPlatform(*world, gameObjectJSON);
      } else {
        LOG_ERROR_SYS(WADLOADER, "Cannot load the following object: {}", std::string(gameObjectJSON));
      }
    }
  }

  return world;
}

std::shared_ptr<CharacterPhysicsComponent> IntegrationWADLoader::loadCharacterPhysicsComponent(
    const nlohmann::json& jsonBody) const {
  std::shared_ptr<CharacterPhysicsComponent> physicsComponent = std::shared_ptr<CharacterPhysicsComponent>(
      new CharacterPhysicsComponent(this->loadRealisticPhysicsComponent(jsonBody)));
  return physicsComponent;
}

void IntegrationWADLoader::loadPlatform(IntegrationWorld& world, const nlohmann::json& jsonBody) const {
  if (jsonBody["enabled"] == "false") {
    return;
  }
  nlohmann::json nameConfig = jsonBody.value("name", "");
  nlohmann::json positionConfig = jsonBody.value("position", nlohmann::json("{}"));
  nlohmann::json physicsConfig = jsonBody.value("physics", nlohmann::json("{}"));
  nlohmann::json graphicsConfig = jsonBody.value("graphics", nlohmann::json("{}"));
  nlohmann::json collisionsConfig = jsonBody.value("collisions", nlohmann::json("{}"));

  EntityName name;
  std::shared_ptr<Platform> platform;
  std::shared_ptr<Identity> identity;
  std::shared_ptr<PositionComponent> positionComponent;
  std::shared_ptr<PhysicsComponent> physicsComponent;
  std::shared_ptr<GraphicsComponent2D> graphicsComponent2D;
  std::shared_ptr<CollisionComponent> collisionComponent;
  for (DuplicationBehavior duplication = DuplicationBehavior(jsonBody.value("duplication", nlohmann::json({})));
       !duplication.done(); duplication.next()) {
    name = EntityName(nameConfig);
    positionComponent = this->loadPositionComponent(positionConfig);
    positionComponent->move(duplication.getOffset() * duplication.getCurr());

    physicsComponent = this->loadRealisticPhysicsComponent(physicsConfig);
    graphicsComponent2D = this->loadGraphicsComponent2D(graphicsConfig);
    collisionComponent = this->loadCollisionComponent(collisionsConfig, positionComponent);

    platform = std::shared_ptr<Platform>(
        new Platform(name, positionComponent, physicsComponent, collisionComponent, graphicsComponent2D));
    platform->inferBoundingBoxFromTexture();

    world.addGameObject(platform);
  }
}

void IntegrationWADLoader::loadCharacter(IntegrationWorld& world, const nlohmann::json& jsonBody) const {
  if (jsonBody["enabled"] == "false") {
    return;
  }
  nlohmann::json nameConfig = jsonBody.value("name", "");
  nlohmann::json positionConfig = jsonBody.value("position", nlohmann::json("{}"));
  nlohmann::json physicsConfig = jsonBody.value("physics", nlohmann::json("{}"));
  nlohmann::json graphicsConfig = jsonBody.value("graphics", nlohmann::json("{}"));
  nlohmann::json collisionsConfig = jsonBody.value("collisions", nlohmann::json("{}"));

  EntityName name;
  std::shared_ptr<Character> character;
  std::shared_ptr<PositionComponent> positionComponent;
  std::shared_ptr<CharacterPhysicsComponent> characterPhysicsComponent;
  std::shared_ptr<GraphicsComponent2D> graphicsComponent2D;
  std::shared_ptr<CollisionComponent> collisionComponent;
  for (DuplicationBehavior duplication = DuplicationBehavior(jsonBody.value("duplicate", nlohmann::json({})));
       !duplication.done(); duplication.next()) {
    name = EntityName(nameConfig);

    positionComponent = this->loadPositionComponent(positionConfig);
    positionComponent->move(duplication.getOffset() * duplication.getCurr());

    characterPhysicsComponent = this->loadCharacterPhysicsComponent(physicsConfig);
    graphicsComponent2D = this->loadGraphicsComponent2D(graphicsConfig);
    collisionComponent = this->loadCollisionComponent(collisionsConfig, positionComponent);

    character = std::shared_ptr<Character>(
        new Character(name, positionComponent, collisionComponent, characterPhysicsComponent, graphicsComponent2D));
    character->inferBoundingBoxFromTexture();
    (jsonBody.value("isPlayerCharacter", false)) ? world.addPlayerCharacter(character) : world.addGameObject(character);
  }
}

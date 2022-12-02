#include "IntegrationWADLoader.hh"

#include <memory>
#include <string>

#include "IntegrationWorld.hh"
#include "Platform.hh"

IntegrationWADLoader::~IntegrationWADLoader() = default;
IntegrationWADLoader::IntegrationWADLoader(const FilePath& wadPath) : WADLoader(wadPath) {}

std::shared_ptr<IntegrationWorld> IntegrationWADLoader::loadIntegrationWorld() const {
  // TODO: Add error checking with helpful messages. Pretending for now that
  // IntegrationWADLoader files are always correctly structured json

  std::shared_ptr<IntegrationWorld> world = std::shared_ptr<IntegrationWorld>(new IntegrationWorld());
  nlohmann::json jsonData = this->getJsonBody();

  if (jsonData.contains("gravityConstant")) {
    world->getPhysicsManager()->setGravityConstant(jsonData["gravityConstant"]);
  }

  if (jsonData.contains("background")) {
    this->loadBackground(*world, jsonData["background"]);
  }

  if (jsonData.contains("gameObjects")) {
    std::shared_ptr<GameObject> object;
    for (auto gameObjectJSON : jsonData["gameObjects"]) {
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

void IntegrationWADLoader::loadBackground(IntegrationWorld& world, const nlohmann::json& jsonBody) const {
  if (!this->objectEnabled(jsonBody)) {
    return;
  }
  std::shared_ptr<Background> background =
      std::shared_ptr<Background>(new Background(EntityName(jsonBody.value("name", ""))));
  std::shared_ptr<PositionComponent> positionComponent =
      this->loadPositionComponent(background->getIdentity(), jsonBody["position"]);
  background->setPositionComponent(positionComponent);
  std::shared_ptr<DrawingComponent> drawingComponent =
      this->loadDrawingComponent(background->getIdentity(), positionComponent, jsonBody["drawing"]);
  background->setDrawingComponent(drawingComponent);
  world.setBackground(background);
}

void IntegrationWADLoader::loadPlatform(IntegrationWorld& world, const nlohmann::json& jsonBody) const {
  if (jsonBody["enabled"] == "false") {
    return;
  }
  nlohmann::json nameConfig = jsonBody.value("name", "");
  nlohmann::json positionConfig = jsonBody.value("position", nlohmann::json("{}"));
  nlohmann::json physicsConfig = jsonBody.value("physics", nlohmann::json("{}"));
  nlohmann::json drawingConfig = jsonBody.value("drawing", nlohmann::json("{}"));
  nlohmann::json collisionsConfig = jsonBody.value("collisions", nlohmann::json("{}"));

  EntityName name;
  std::shared_ptr<Platform> platform;
  std::shared_ptr<Identity> identity;
  std::shared_ptr<PositionComponent> positionComponent;
  std::shared_ptr<PhysicsComponent> physicsComponent;
  std::shared_ptr<DrawingComponent> drawingComponent;
  std::shared_ptr<CollisionComponent> collisionComponent;
  for (DuplicationBehavior duplication = DuplicationBehavior(jsonBody.value("duplication", nlohmann::json({})));
       !duplication.done(); duplication.next()) {
    name = EntityName(nameConfig);
    platform = std::shared_ptr<Platform>(new Platform(name));
    identity = platform->getIdentity();

    positionComponent = this->loadPositionComponent(identity, positionConfig);
    positionComponent->move(duplication.getOffset() * duplication.getCurr());
    platform->setPositionComponent(positionComponent);

    physicsComponent = this->loadPhysicsComponent(identity, physicsConfig);
    platform->setPhysicsComponent(physicsComponent);

    drawingComponent = this->loadDrawingComponent(identity, positionComponent, drawingConfig);
    platform->setDrawingComponent(drawingComponent);

    collisionComponent = this->loadCollisionComponent(identity, positionComponent, collisionsConfig);

    platform->setCollisionComponent(collisionComponent);
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
  nlohmann::json drawingConfig = jsonBody.value("drawing", nlohmann::json("{}"));
  nlohmann::json collisionsConfig = jsonBody.value("collisions", nlohmann::json("{}"));

  EntityName name;
  std::shared_ptr<Character> character;
  std::shared_ptr<PositionComponent> positionComponent;
  std::shared_ptr<PhysicsComponent> physicsComponent;
  std::shared_ptr<CharacterPhysicsComponent> characterPhysicsComponent;
  std::shared_ptr<DrawingComponent> drawingComponent;
  std::shared_ptr<CollisionComponent> collisionComponent;
  for (DuplicationBehavior duplication = DuplicationBehavior(jsonBody.value("duplicate", nlohmann::json({})));
       !duplication.done(); duplication.next()) {
    name = EntityName(nameConfig);
    character = std::shared_ptr<Character>(new Character(name));

    positionComponent = this->loadPositionComponent(character->getIdentity(), positionConfig);
    positionComponent->move(duplication.getOffset() * duplication.getCurr());
    character->setPositionComponent(positionComponent);

    physicsComponent = this->loadPhysicsComponent(character->getIdentity(), physicsConfig);
    characterPhysicsComponent =
        std::shared_ptr<CharacterPhysicsComponent>(new CharacterPhysicsComponent(physicsComponent));
    character->setPhysicsComponent(characterPhysicsComponent);

    drawingComponent = this->loadDrawingComponent(character->getIdentity(), positionComponent, drawingConfig);
    character->setDrawingComponent(drawingComponent);

    collisionComponent = this->loadCollisionComponent(character->getIdentity(), positionComponent, collisionsConfig);
    character->setCollisionComponent(collisionComponent);
    character->inferBoundingBoxFromTexture();
    (jsonBody.value("isPlayerCharacter", false)) ? world.addPlayerCharacter(character) : world.addGameObject(character);
  }
}

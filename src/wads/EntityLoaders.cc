#include "WADLoader.hh"
#include "Zone.hh"

shared_ptr<Zone> WADLoader::loadZone(const json& zoneData) const {
  // TODO: Add error checking with helpful messages. Pretending for now that
  // WADLoader files are always correctly structured json

  shared_ptr<Zone> zone = shared_ptr<Zone>(new Zone());
  if (zoneData.contains("gravityConstant")) {
    zone->setGravityConstant(zoneData["gravityConstant"]);
  }

  if (zoneData.contains("background")) {
    this->loadBackground(*zone, zoneData["background"]);
  }

  if (zoneData.contains("gameObjects")) {
    shared_ptr<GameObject> object;
    for (auto gameObjectJSON : zoneData["gameObjects"]) {
      LOG_DEBUG_SYS(WADLOADER, "Loading GameObject: {0}", to_string(gameObjectJSON));
      if (gameObjectJSON["type"] == "Character") {
        this->loadCharacter(*zone, gameObjectJSON);
      } else if (gameObjectJSON["type"] == "Platform") {
        this->loadPlatform(*zone, gameObjectJSON);
      } else {
        LOG_ERROR_SYS(WADLOADER, "Cannot load the following object: {}", string(gameObjectJSON));
      }
    }
  }

  return zone;
}

void WADLoader::loadBackground(Zone& zone, const json& jsonBody) const {
  if (!this->objectEnabled(jsonBody)) {
    return;
  }
  shared_ptr<Background> background = shared_ptr<Background>(new Background(EntityName(jsonBody.value("name", ""))));
  shared_ptr<PositionComponent> positionComponent =
      this->loadPositionComponent(background->getIdentity(), jsonBody["position"]);
  background->setPositionComponent(positionComponent);
  shared_ptr<DrawingComponent> drawingComponent =
      this->loadDrawingComponent(background->getIdentity(), positionComponent, jsonBody["drawing"]);
  background->setDrawingComponent(drawingComponent);
  zone.setBackground(background);
}

void WADLoader::loadPlatform(Zone& zone, const json& jsonBody) const {
  if (jsonBody["enabled"] == "false") {
    return;
  }
  json nameConfig = jsonBody.value("name", "");
  json positionConfig = jsonBody.value("position", json("{}"));
  json physicsConfig = jsonBody.value("physics", json("{}"));
  json drawingConfig = jsonBody.value("drawing", json("{}"));
  json collisionsConfig = jsonBody.value("collisions", json("{}"));

  EntityName name;
  shared_ptr<Platform> platform;
  shared_ptr<Identity> identity;
  shared_ptr<PositionComponent> positionComponent;
  shared_ptr<PhysicsComponent> physicsComponent;
  shared_ptr<DrawingComponent> drawingComponent;
  shared_ptr<CollisionComponent> collisionComponent;
  for (DuplicationBehavior duplication = DuplicationBehavior(jsonBody.value("duplication", json({})));
       !duplication.done(); duplication.next()) {
    name = EntityName(nameConfig);
    platform = shared_ptr<Platform>(new Platform(name));
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

    zone.addGameObject(platform);
  }
}

void WADLoader::loadCharacter(Zone& zone, const json& jsonBody) const {
  if (jsonBody["enabled"] == "false") {
    return;
  }
  json nameConfig = jsonBody.value("name", "");
  json positionConfig = jsonBody.value("position", json("{}"));
  json physicsConfig = jsonBody.value("physics", json("{}"));
  json drawingConfig = jsonBody.value("drawing", json("{}"));
  json collisionsConfig = jsonBody.value("collisions", json("{}"));

  EntityName name;
  shared_ptr<Character> character;
  shared_ptr<PositionComponent> positionComponent;
  shared_ptr<PhysicsComponent> physicsComponent;
  shared_ptr<CharacterPhysicsComponent> characterPhysicsComponent;
  shared_ptr<DrawingComponent> drawingComponent;
  shared_ptr<CollisionComponent> collisionComponent;
  for (DuplicationBehavior duplication = DuplicationBehavior(jsonBody.value("duplicate", json({})));
       !duplication.done(); duplication.next()) {
    name = EntityName(nameConfig);
    character = shared_ptr<Character>(new Character(name));

    positionComponent = this->loadPositionComponent(character->getIdentity(), positionConfig);
    positionComponent->move(duplication.getOffset() * duplication.getCurr());
    character->setPositionComponent(positionComponent);

    physicsComponent = this->loadPhysicsComponent(character->getIdentity(), physicsConfig);
    characterPhysicsComponent = shared_ptr<CharacterPhysicsComponent>(new CharacterPhysicsComponent(physicsComponent));
    character->setPhysicsComponent(characterPhysicsComponent);

    drawingComponent = this->loadDrawingComponent(character->getIdentity(), positionComponent, drawingConfig);
    character->setDrawingComponent(drawingComponent);

    collisionComponent = this->loadCollisionComponent(character->getIdentity(), positionComponent, collisionsConfig);
    character->setCollisionComponent(collisionComponent);
    character->inferBoundingBoxFromTexture();
    (jsonBody.value("isPlayerCharacter", false)) ? zone.addPlayerCharacter(character) : zone.addGameObject(character);
  }
}

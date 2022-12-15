#include "PorngWADLoader.hh"

/*
 * TODO: This implementation is pretty stinky (lots of code repetition) but presently very straightforward. It is super
 * annoying for a game programmer to need to do all of this unnecessary json reading and instantiation; we might really
 * benefit from having something like a Visitor or "game object initializer"
 */

/*
 * TODO: Should it really be a problem for a component not to have an associated identity? The component just knows
 * about the data it manages, and how to manipulate it. From the game's perspective, an "identity-less component" has no
 * associated game object so it doesn't represent anything meaningful. Not being able to instantiate components without
 * identities leads to the awkward instantiation below.
 */

PorngWADLoader::PorngWADLoader(const FilePath& wadPath) : WADLoader(wadPath) {}

PorngWADLoader::~PorngWADLoader() = default;

std::shared_ptr<PorngWorld> PorngWADLoader::loadPorngWorld() const {
  // TODO: Add error checking with helpful messages. Pretending for now that
  // IntegrationWADLoader files are always correctly structured json
  nlohmann::json jsonData = this->getJsonBody();
  std::shared_ptr<PorngWorld> world =
      std::shared_ptr<PorngWorld>(new PorngWorld(this->loadGraphicsSettings(jsonData["graphics"])));

  if (jsonData.contains("gravityConstant")) {
    world->getPhysicsManager().setGravityConstant(jsonData["gravityConstant"]);
  }

  if (jsonData.contains("background")) {
    this->loadBackground(*world, jsonData["background"]);
  }

  if (jsonData.contains("gameObjects")) {
    std::shared_ptr<GameObject> object;
    for (auto gameObjectJSON : jsonData["gameObjects"]) {
      LOG_DEBUG_SYS(WADLOADER, "Loading GameObject: {0}", nlohmann::to_string(gameObjectJSON));
      if (gameObjectJSON["type"] == "Ball") {
        this->loadBall(*world, gameObjectJSON);
      } else if (gameObjectJSON["type"] == "Net") {
        this->loadNet(*world, gameObjectJSON);
      } else if (gameObjectJSON["type"] == "Paddle") {
        this->loadPaddle(*world, gameObjectJSON);
      } else {
        LOG_ERROR_SYS(WADLOADER, "Cannot load the following object: {}", std::string(gameObjectJSON));
      }
    }
  }

  return world;
}

void PorngWADLoader::loadBall(PorngWorld& world, const nlohmann::json& jsonBody) const {
  if (jsonBody["enabled"] == "false") {
    return;
  }
  nlohmann::json nameConfig = jsonBody.value("name", "");
  nlohmann::json positionConfig = jsonBody.value("position", nlohmann::json("{}"));
  nlohmann::json physicsConfig = jsonBody.value("physics", nlohmann::json("{}"));
  nlohmann::json collisionsConfig = jsonBody.value("collisions", nlohmann::json("{}"));
  nlohmann::json drawingConfig = jsonBody.value("drawing", nlohmann::json("{}"));

  EntityName name;
  std::shared_ptr<Ball> ball;
  std::shared_ptr<Identity> identity;
  std::shared_ptr<PositionComponent> positionComponent;
  std::shared_ptr<SimplePhysicsComponent> physicsComponent;
  std::shared_ptr<CollisionComponent> collisionComponent;
  std::shared_ptr<DrawingComponent> drawingComponent;
  for (DuplicationBehavior duplication = DuplicationBehavior(jsonBody.value("duplication", nlohmann::json({})));
       !duplication.done(); duplication.next()) {
    name = EntityName(nameConfig);
    positionComponent = this->loadPositionComponent(positionConfig);
    positionComponent->move(duplication.getOffset() * duplication.getCurr());
    physicsComponent = this->loadSimplePhysicsComponent(physicsConfig);
    collisionComponent = this->loadCollisionComponent(collisionsConfig, positionComponent);
    drawingComponent = this->loadDrawingComponent(drawingConfig);
    ball = std::shared_ptr<Ball>(
        new Ball(name, positionComponent, physicsComponent, collisionComponent, drawingComponent));
    ball->inferBoundingBoxFromTexture();

    world.addGameObject(ball);
  }
}

void PorngWADLoader::loadNet(PorngWorld& world, const nlohmann::json& jsonBody) const {
  if (jsonBody["enabled"] == "false") {
    return;
  }
  nlohmann::json nameConfig = jsonBody.value("name", "");
  nlohmann::json positionConfig = jsonBody.value("position", nlohmann::json("{}"));
  nlohmann::json physicsConfig = jsonBody.value("physics", nlohmann::json("{}"));
  nlohmann::json drawingConfig = jsonBody.value("drawing", nlohmann::json("{}"));
  nlohmann::json collisionsConfig = jsonBody.value("collisions", nlohmann::json("{}"));

  EntityName name;
  std::shared_ptr<Net> net;
  std::shared_ptr<Identity> identity;
  std::shared_ptr<PositionComponent> positionComponent;
  std::shared_ptr<SimplePhysicsComponent> physicsComponent;
  std::shared_ptr<DrawingComponent> drawingComponent;
  for (DuplicationBehavior duplication = DuplicationBehavior(jsonBody.value("duplication", nlohmann::json({})));
       !duplication.done(); duplication.next()) {
    name = EntityName(nameConfig);
    positionComponent = this->loadPositionComponent(positionConfig);
    positionComponent->move(duplication.getOffset() * duplication.getCurr());
    drawingComponent = this->loadDrawingComponent(drawingConfig);
    net = std::shared_ptr<Net>(new Net(name, positionComponent, drawingComponent));
    world.addGameObject(net);
  }
}

void PorngWADLoader::loadPaddle(PorngWorld& world, const nlohmann::json& jsonBody) const {
  if (jsonBody["enabled"] == "false") {
    return;
  }
  nlohmann::json nameConfig = jsonBody.value("name", "");
  nlohmann::json positionConfig = jsonBody.value("position", nlohmann::json("{}"));
  nlohmann::json physicsConfig = jsonBody.value("physics", nlohmann::json("{}"));
  nlohmann::json drawingConfig = jsonBody.value("drawing", nlohmann::json("{}"));
  nlohmann::json collisionsConfig = jsonBody.value("collisions", nlohmann::json("{}"));

  EntityName name;
  std::shared_ptr<Paddle> paddle;
  std::shared_ptr<Identity> identity;
  std::shared_ptr<PositionComponent> positionComponent;
  std::shared_ptr<SimplePhysicsComponent> physicsComponent;
  std::shared_ptr<DrawingComponent> drawingComponent;
  std::shared_ptr<CollisionComponent> collisionComponent;
  for (DuplicationBehavior duplication = DuplicationBehavior(jsonBody.value("duplication", nlohmann::json({})));
       !duplication.done(); duplication.next()) {
    name = EntityName(nameConfig);

    positionComponent = this->loadPositionComponent(positionConfig);
    positionComponent->move(duplication.getOffset() * duplication.getCurr());
    physicsComponent = this->loadSimplePhysicsComponent(physicsConfig);
    collisionComponent = this->loadCollisionComponent(collisionsConfig, positionComponent);
    drawingComponent = this->loadDrawingComponent(drawingConfig);

    paddle = std::shared_ptr<Paddle>(
        new Paddle(name, positionComponent, physicsComponent, collisionComponent, drawingComponent));
    paddle->inferBoundingBoxFromTexture();

    world.addGameObject(paddle);
  }
}

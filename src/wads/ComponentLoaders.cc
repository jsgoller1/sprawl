#include <memory>
#include <string>

#include "CollisionComponent.hh"
#include "DrawingComponent.hh"
#include "PhysicsComponent.hh"
#include "PositionComponent.hh"
#include "Texture.hh"
#include "WADLoader.hh"

std::shared_ptr<PositionComponent> WADLoader::loadPositionComponent(const std::shared_ptr<Identity> ownerIdentity,
                                                                    const nlohmann::json& jsonBody) const {
  PositionUnit x = jsonBody.value("x", 0.0);
  LOG_DEBUG_SYS(WADLOADER, "{0}, Setting PositionComponent.x = {1}", *ownerIdentity->getEntityID(), x);

  PositionUnit y = jsonBody.value("y", 0.0);
  LOG_DEBUG_SYS(WADLOADER, "{0}, Setting PositionComponent.y = {1}", *ownerIdentity->getEntityID(), y);
  return std::shared_ptr<PositionComponent>(new PositionComponent(ownerIdentity, x, y));
}

std::shared_ptr<DrawingComponent> WADLoader::loadDrawingComponent(
    const std::shared_ptr<Identity> ownerIdentity, const std::shared_ptr<PositionComponent> positionComponent,
    const nlohmann::json& jsonBody) const {
  std::shared_ptr<Texture> texture;
  std::string texturePath = jsonBody.value("texturePath", "");
  if (texturePath != "") {
    texture = std::shared_ptr<Texture>(new Texture(this->_wadDir + texturePath));
  } else {
    texture = nullptr;
    LOG_ERROR("No texture loaded for {0}.", ownerIdentity->toString());
  }
  return std::shared_ptr<DrawingComponent>(new DrawingComponent(ownerIdentity, positionComponent, texture));
}

std::shared_ptr<CollisionComponent> WADLoader::loadCollisionComponent(
    const std::shared_ptr<Identity> ownerIdentity, const std::shared_ptr<PositionComponent> positionComponent,
    const nlohmann::json& jsonBody) const {
  (void)jsonBody;
  /*
  bool collisionsEnabled;
  if (jsonBody.contains("enabled")) {
    collisionsEnabled = jsonBody.value("enabled", "false") == "true";
  }
  */
  return std::shared_ptr<CollisionComponent>(new CollisionComponent(ownerIdentity, positionComponent));
}

std::shared_ptr<PhysicsComponent> WADLoader::loadPhysicsComponent(const std::shared_ptr<Identity> ownerIdentity,
                                                                  const nlohmann::json& jsonBody) const {
  std::shared_ptr<PhysicsComponent> physicsComponent =
      std::shared_ptr<PhysicsComponent>(new PhysicsComponent(ownerIdentity));

  physicsComponent->dragCoefficient(jsonBody.value("dragCoefficient", 0.0));
  physicsComponent->dragType((jsonBody.value("dragType", "linear") == "linear") ? DragType::LINEAR
                                                                                : DragType::TIME_EXPONENTIAL);
  physicsComponent->maxSpeed(jsonBody.value("maxSpeed", 0.0));
  physicsComponent->minSpeed(jsonBody.value("minSpeed", 0.0));
  physicsComponent->gravityEnabled(jsonBody.value("gravityEnabled", true));
  physicsComponent->forceEnabled(jsonBody.value("forceEnabled", true));
  return physicsComponent;
}

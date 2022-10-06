#include "CollisionComponent.hh"
#include "DrawingComponent.hh"
#include "PhysicsComponent.hh"
#include "PositionComponent.hh"
#include "Texture.hh"
#include "WADLoader.hh"

shared_ptr<PositionComponent> WADLoader::loadPositionComponent(const shared_ptr<Identity> ownerIdentity,
                                                               const json& jsonBody) const {
  PositionUnit x = jsonBody.value("x", 0.0);
  LOG_DEBUG_SYS(WADLOADER, "{0}, Setting PositionComponent.x = {1}", *ownerIdentity->getEntityID(), x);

  PositionUnit y = jsonBody.value("y", 0.0);
  LOG_DEBUG_SYS(WADLOADER, "{0}, Setting PositionComponent.y = {1}", *ownerIdentity->getEntityID(), y);
  return shared_ptr<PositionComponent>(new PositionComponent(ownerIdentity, x, y));
}

shared_ptr<DrawingComponent> WADLoader::loadDrawingComponent(const shared_ptr<Identity> ownerIdentity,
                                                             const shared_ptr<PositionComponent> positionComponent,
                                                             const json& jsonBody) const {
  shared_ptr<Texture> texture;
  string texturePath = jsonBody.value("texturePath", "");
  if (texturePath != "") {
    texture = shared_ptr<Texture>(new Texture(this->_wadDir + texturePath));
  } else {
    texture = nullptr;
    LOG_ERROR("No texture loaded for {0}.", ownerIdentity->toString());
  }
  return shared_ptr<DrawingComponent>(new DrawingComponent(ownerIdentity, positionComponent, texture));
}

shared_ptr<CollisionComponent> WADLoader::loadCollisionComponent(const shared_ptr<Identity> ownerIdentity,
                                                                 const shared_ptr<PositionComponent> positionComponent,
                                                                 const json& jsonBody) const {
  (void)jsonBody;
  /*
  bool collisionsEnabled;
  if (jsonBody.contains("enabled")) {
    collisionsEnabled = jsonBody.value("enabled", "false") == "true";
  }
  */
  return shared_ptr<CollisionComponent>(new CollisionComponent(ownerIdentity, positionComponent));
}

shared_ptr<PhysicsComponent> WADLoader::loadPhysicsComponent(const shared_ptr<Identity> ownerIdentity,
                                                             const json& jsonBody) const {
  shared_ptr<PhysicsComponent> physicsComponent = shared_ptr<PhysicsComponent>(new PhysicsComponent(ownerIdentity));

  physicsComponent->dragCoefficient(jsonBody.value("dragCoefficient", 0.0));
  physicsComponent->dragType((jsonBody.value("dragType", "linear") == "linear") ? DragType::LINEAR
                                                                                : DragType::TIME_EXPONENTIAL);
  physicsComponent->maxSpeed(jsonBody.value("maxSpeed", 0.0));
  physicsComponent->minSpeed(jsonBody.value("minSpeed", 0.0));
  physicsComponent->gravityEnabled(jsonBody.value("gravityEnabled", true));
  physicsComponent->forceEnabled(jsonBody.value("forceEnabled", true));
  return physicsComponent;
}

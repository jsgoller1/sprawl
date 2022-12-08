#include <memory>
#include <string>

#include "CollisionComponent.hh"
#include "DrawingComponent.hh"
#include "Logging.hh"
#include "PhysicsComponent.hh"
#include "PositionComponent.hh"
#include "Texture.hh"
#include "WADLoader.hh"

std::shared_ptr<PositionComponent> WADLoader::loadPositionComponent(const nlohmann::json& jsonBody) const {
  PositionUnit x = jsonBody.value("x", 0.0);
  PositionUnit y = jsonBody.value("y", 0.0);
  PositionUnit height = jsonBody.value("height", 1.0);
  PositionUnit width = jsonBody.value("width", 1.0);
  LOG_DEBUG_SYS(WADLOADER, "Setting PositionComponent(center=Vect2D({1},{2}),height={3},width={4})", x, y, height,
                width);
  return std::shared_ptr<PositionComponent>(new PositionComponent(nullptr, Vect2D(x, y), height, width));
}

std::shared_ptr<PhysicsComponent> WADLoader::loadPhysicsComponent(const nlohmann::json& jsonBody) const {
  std::shared_ptr<PhysicsComponent> physicsComponent = std::shared_ptr<PhysicsComponent>(new PhysicsComponent());

  physicsComponent->dragCoefficient(jsonBody.value("dragCoefficient", 0.0));
  physicsComponent->dragType((jsonBody.value("dragType", "linear") == "linear") ? DragType::LINEAR
                                                                                : DragType::TIME_EXPONENTIAL);
  physicsComponent->maxSpeed(jsonBody.value("maxSpeed", 0.0));
  physicsComponent->minSpeed(jsonBody.value("minSpeed", 0.0));
  physicsComponent->gravityEnabled(jsonBody.value("gravityEnabled", true));
  physicsComponent->forceEnabled(jsonBody.value("forceEnabled", true));
  return physicsComponent;
}

std::shared_ptr<DrawingComponent> WADLoader::loadDrawingComponent(const nlohmann::json& jsonBody) const {
  std::shared_ptr<Texture> texture;
  std::string texturePath = jsonBody.value("texturePath", "");
  if (texturePath != "") {
    texture = std::shared_ptr<Texture>(new Texture(this->_wadDir + texturePath));
  } else {
    texture = nullptr;
    LOG_ERROR("No texture loaded.");
  }
  return std::shared_ptr<DrawingComponent>(new DrawingComponent(nullptr, texture));
}

std::shared_ptr<CollisionComponent> WADLoader::loadCollisionComponent(
    const nlohmann::json& jsonBody, const std::shared_ptr<PositionComponent> positionComponent) const {
  (void)jsonBody;
  /*
  bool collisionsEnabled;
  if (jsonBody.contains("enabled")) {
    collisionsEnabled = jsonBody.value("enabled", "false") == "true";
  }
  */
  return std::shared_ptr<CollisionComponent>(new CollisionComponent(nullptr, positionComponent));
}

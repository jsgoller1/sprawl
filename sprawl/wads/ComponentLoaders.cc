#include <memory>
#include <string>

#include "CharacterPhysicsComponent.hh"
#include "CollisionComponent.hh"
#include "DrawingComponent.hh"
#include "Logging.hh"
#include "PositionComponent.hh"
#include "RealisticPhysicsComponent.hh"
#include "SimplePhysicsComponent.hh"
#include "Texture.hh"
#include "WADLoader.hh"

std::shared_ptr<PositionComponent> WADLoader::loadPositionComponent(const nlohmann::json& jsonBody) const {
  PositionUnit x = jsonBody.value("x", 0.0);
  LOG_DEBUG_SYS(WADLOADER, "Setting PositionComponent.x = {1}", x);

  PositionUnit y = jsonBody.value("y", 0.0);
  LOG_DEBUG_SYS(WADLOADER, "Setting PositionComponent.y = {1}", y);
  return std::shared_ptr<PositionComponent>(new PositionComponent(nullptr, x, y));
}

std::shared_ptr<DrawingComponent> WADLoader::loadDrawingComponent(
    const nlohmann::json& jsonBody, const std::shared_ptr<PositionComponent> positionComponent) const {
  std::shared_ptr<Texture> texture;
  std::string texturePath = jsonBody.value("texturePath", "");
  if (texturePath != "") {
    texture = std::shared_ptr<Texture>(new Texture(this->_wadDir + texturePath));
  } else {
    texture = nullptr;
    LOG_ERROR("No texture loaded.");
  }
  return std::shared_ptr<DrawingComponent>(new DrawingComponent(nullptr, positionComponent, texture));
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

std::shared_ptr<SimplePhysicsComponent> WADLoader::loadSimplePhysicsComponent(const nlohmann::json& jsonBody) const {
  return std::shared_ptr<SimplePhysicsComponent>(new SimplePhysicsComponent(
      nullptr, jsonBody.value("minSpeed", 0.0), jsonBody.value("maxSpeed", 0.0), Vect2D::zero()));
}

std::shared_ptr<RealisticPhysicsComponent> WADLoader::loadRealisticPhysicsComponent(
    const nlohmann::json& jsonBody) const {
  return std::shared_ptr<RealisticPhysicsComponent>(new RealisticPhysicsComponent(
      nullptr, jsonBody.value("forceEnabled", true), jsonBody.value("gravityEnabled", true),
      (jsonBody.value("dragType", "linear") == "linear" ? DragType::LINEAR : DragType::TIME_EXPONENTIAL),
      jsonBody.value("dragCoefficient", 0.0), jsonBody.value("minSpeed", 0.0), jsonBody.value("maxSpeed", 0.0),
      Vect2D::zero()));
}

std::shared_ptr<CharacterPhysicsComponent> WADLoader::loadCharacterPhysicsComponent(
    const nlohmann::json& jsonBody) const {
  return std::shared_ptr<CharacterPhysicsComponent>(
      new CharacterPhysicsComponent(this->loadRealisticPhysicsComponent(jsonBody)));
}

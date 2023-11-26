#include <memory>
#include <string>

#include "Actor.hh"
#include "CollisionComponent.hh"
#include "DrawingComponent.hh"
#include "Logging.hh"
#include "PositionComponent.hh"
#include "RealisticPhysicsComponent.hh"
#include "Texture.hh"
#include "WADLoader.hh"

void WADLoader::loadPositionComponent(std::shared_ptr<Actor> owner, const nlohmann::json& jsonBody) const {
  PositionUnit x = jsonBody.value("x", 0.0);
  PositionUnit y = jsonBody.value("y", 0.0);
  PositionUnit height = jsonBody.value("height", 1.0);
  PositionUnit width = jsonBody.value("width", 1.0);
  LOG_DEBUG_SYS(WADLOADER, "Setting PositionComponent(center=Vect2D({1},{2}),height={3},width={4})", x, y, height,
                width);
  owner->addComponent(std::make_shared<PositionComponent>(owner, Vect2D(x, y), height, width));
}

void WADLoader::loadRealisticPhysicsComponent(std::shared_ptr<Actor> owner, const nlohmann::json& jsonBody) const {
  std::shared_ptr<RealisticPhysicsComponent> physicsComponent =
      std::shared_ptr<RealisticPhysicsComponent>(new RealisticPhysicsComponent(owner));

  physicsComponent->dragCoefficient(jsonBody.value("dragCoefficient", 0.0));
  physicsComponent->dragType((jsonBody.value("dragType", "linear") == "linear") ? DragType::LINEAR
                                                                                : DragType::TIME_EXPONENTIAL);
  physicsComponent->setMaxSpeed(jsonBody.value("maxSpeed", 0.0));
  physicsComponent->setMinSpeed(jsonBody.value("minSpeed", 0.0));
  physicsComponent->gravityEnabled(jsonBody.value("gravityEnabled", true));
  physicsComponent->forceEnabled(jsonBody.value("forceEnabled", true));

  owner->addComponent(physicsComponent);
}

void WADLoader::loadDrawingComponent(std::shared_ptr<Actor> owner, const nlohmann::json& jsonBody) const {
  std::shared_ptr<Texture> texture;
  std::string texturePath = jsonBody.value("texturePath", "");
  if (texturePath != "") {
    texture = std::shared_ptr<Texture>(new Texture(this->_wadDir + texturePath));
  } else {
    texture = nullptr;
    LOG_ERROR("No texture loaded.");
  }
  owner->addComponent(std::make_shared<DrawingComponent>(owner, texture));
}

void WADLoader::loadCollisionComponent(std::shared_ptr<Actor> owner, const nlohmann::json& jsonBody) const {
  (void)jsonBody;
  /*
  bool collisionsEnabled;
  if (jsonBody.contains("enabled")) {
    collisionsEnabled = jsonBody.value("enabled", "false") == "true";
  }
  */
  owner->addComponent(std::make_shared<CollisionComponent>(owner));
}

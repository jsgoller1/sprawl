#include <memory>
#include <string>

#include "Actor.hh"
#include "BehaviorComponentFactory.hh"
#include "CollisionComponent.hh"
#include "DrawingComponent.hh"
#include "IBehaviorComponent.hh"
#include "Logging.hh"
#include "PhysicsComponent.hh"
#include "PositionComponent.hh"
#include "Texture.hh"
#include "WADLoader.hh"

void WADLoader::loadBehaviorComponent(std::shared_ptr<Actor> owner, const nlohmann::json& jsonBody) const {
  std::string typeName = jsonBody.value("type", "");
  std::shared_ptr<IBehaviorComponent> component = BehaviorComponentFactory::CreateComponent(typeName);
  if (component) {
    component->setOwner(owner);
    component->managerRegister();
    owner->addComponent(typeName, component);
    component->initializeBindables(BehaviorComponentConfig(jsonBody));
  } else {
    LOG_ERROR("Unknown component type: {0}", typeName);
  }
}

void WADLoader::loadCollisionComponent(std::shared_ptr<Actor> owner, const nlohmann::json& jsonBody) const {
  (void)jsonBody;
  /*
  bool collisionsEnabled;
  if (jsonBody.contains("enabled")) {
    collisionsEnabled = jsonBody.value("enabled", "false") == "true";
  }
  */
  std::shared_ptr<CollisionComponent> component = std::make_shared<CollisionComponent>();
  component->setOwner(owner);
  component->managerRegister();
  owner->addComponent(COLLISION_COMPONENT_NAME, component);
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
  std::shared_ptr<DrawingComponent> component = std::shared_ptr<DrawingComponent>(new DrawingComponent(texture));
  component->setOwner(owner);
  component->managerRegister();
  owner->addComponent(DRAWING_COMPONENT_NAME, component);
}

void WADLoader::loadPositionComponent(std::shared_ptr<Actor> owner, const nlohmann::json& jsonBody) const {
  PositionUnit x = jsonBody.value("x", 0.0);
  PositionUnit y = jsonBody.value("y", 0.0);
  PositionUnit height = jsonBody.value("height", 1.0);
  PositionUnit width = jsonBody.value("width", 1.0);
  LOG_DEBUG_SYS(WADLOADER, "Setting PositionComponent(center=Vect2D({0},{1}),height={2},width={3})", x, y, height,
                width);

  std::shared_ptr<PositionComponent> component = std::make_shared<PositionComponent>(Vect2D(x, y), height, width);
  component->setOwner(owner);
  owner->addComponent(POSITION_COMPONENT_NAME, component);
}

void WADLoader::loadPhysicsComponent(std::shared_ptr<Actor> owner, const nlohmann::json& jsonBody) const {
  std::shared_ptr<PhysicsComponent> component = std::make_shared<PhysicsComponent>();
  component->setOwner(owner);
  component->managerRegister();

  component->dragCoefficient(jsonBody.value("dragCoefficient", 0.0));
  component->dragType((jsonBody.value("dragType", "linear") == "linear") ? DragType::LINEAR
                                                                         : DragType::TIME_EXPONENTIAL);
  component->setMaxSpeed(jsonBody.value("maxSpeed", 0.0));
  component->setMinSpeed(jsonBody.value("minSpeed", 0.0));
  component->gravityEnabled(jsonBody.value("gravityEnabled", false));
  component->forceEnabled(jsonBody.value("forceEnabled", false));

  owner->addComponent(PHYSICS_COMPONENT_NAME, component);
}

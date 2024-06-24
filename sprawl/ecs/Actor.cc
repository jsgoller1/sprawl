#include "Actor.hh"

#include "Component.hh"

std::string Actor::toString() const { return fmt::format("Actor: {} ()", this->getUUID(), this->name); }

bool Actor::isEnabled() const { return this->enabled; }
void Actor::setEnabled(const bool setting) { this->enabled = setting; }
EntityName Actor::getName() const { return this->name; }
void Actor::setName(const EntityName name) { this->name = name; }

void Actor::addComponent(const std::string componentTypeName, const std::shared_ptr<Component> component) {
  this->components.emplace(std::make_pair(componentTypeName, component));
}
void Actor::removeComponent(const UUID uuid) { this->components.erase(uuid); }
void Actor::removeComponent(const std::shared_ptr<Component> component) {
  this->components.erase(component->getUUID());
}

Actor::Actor(const EntityName name) : Entity() { this->name = name; }

/*
void Actor::inferBoundingBoxFromTexture() {
  std::shared_ptr<Texture> texture = this->graphicsComponent2D->getTexture();
  this->collisionComponent->height(texture->getHeight());
  this->collisionComponent->width(texture->getWidth());
}
*/

#pragma once

#include "DrawingComponent.hh"
#include "Entity.hh"
#include "PositionComponent.hh"
#include "Screen.hh"
#include "Texture.hh"
#include "Types.hh"

class Background : public Entity {
 public:
  Background(const EntityName entityName = EntityName(""),
             const std::shared_ptr<PositionComponent> positionComponent = nullptr,
             const std::shared_ptr<DrawingComponent> drawingComponent = nullptr)
      : Entity(entityName) {
    this->positionComponent = (positionComponent == nullptr)
                                  ? std::shared_ptr<PositionComponent>(new PositionComponent(this->getIdentity()))
                                  : positionComponent;
    this->drawingComponent =
        (drawingComponent == nullptr)
            ? std::shared_ptr<DrawingComponent>(new DrawingComponent(this->getIdentity(), this->positionComponent))
            : drawingComponent;
  }

  std::shared_ptr<PositionComponent> getPositionComponent() const { return this->positionComponent; }

  void setPositionComponent(const std::shared_ptr<PositionComponent> positionComponent) {
    this->positionComponent = positionComponent;
  }

  std::shared_ptr<DrawingComponent> getDrawingComponent() const { return this->drawingComponent; }
  void setDrawingComponent(const std::shared_ptr<DrawingComponent> drawingComponent) {
    this->drawingComponent = drawingComponent;
  }

 private:
  std::shared_ptr<PositionComponent> positionComponent;
  std::shared_ptr<DrawingComponent> drawingComponent;
};
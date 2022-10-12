#pragma once

#include "DrawingComponent.hh"
#include "Entity.hh"
#include "PositionComponent.hh"
#include "Screen.hh"
#include "Texture.hh"
#include "Types.hh"

class Background : public Entity {
 public:
  Background(const shared_ptr<EntityName> entityName = nullptr,
             const shared_ptr<PositionComponent> positionComponent = nullptr,
             const shared_ptr<DrawingComponent> drawingComponent = nullptr)
      : Entity(entityName) {
    this->positionComponent =
        (positionComponent == nullptr)
            ? shared_ptr<PositionComponent>(new PositionComponent())
            : positionComponent;
    this->drawingComponent =
        (drawingComponent == nullptr)
            ? shared_ptr<DrawingComponent>(
                  new DrawingComponent(this->positionComponent))
            : drawingComponent;
  }

  shared_ptr<PositionComponent> getPositionComponent() const {
    return this->positionComponent;
  }

  void setPositionComponent(
      const shared_ptr<PositionComponent> positionComponent) {
    this->positionComponent = positionComponent;
  }

  shared_ptr<DrawingComponent> getDrawingComponent() const {
    return this->drawingComponent;
  }
  void setDrawingComp(const shared_ptr<DrawingComponent> drawingComponent) {
    this->drawingComponent = drawingComponent;
  }

 private:
  shared_ptr<PositionComponent> positionComponent;
  shared_ptr<DrawingComponent> drawingComponent;
};

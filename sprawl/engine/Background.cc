#include "Background.hh"

Background::Background(const EntityName entityName, const std::shared_ptr<PositionComponent> positionComponent,
                       const std::shared_ptr<DrawingComponent> drawingComponent)
    : Entity(entityName) {
  this->positionComponent = (positionComponent == nullptr)
                                ? std::shared_ptr<PositionComponent>(new PositionComponent(this->getIdentity()))
                                : positionComponent;
  this->drawingComponent =
      (drawingComponent == nullptr)
          ? std::shared_ptr<DrawingComponent>(new DrawingComponent(this->getIdentity(), this->positionComponent))
          : drawingComponent;
}

std::shared_ptr<PositionComponent> Background::getPositionComponent() const { return this->positionComponent; }

void Background::setPositionComponent(const std::shared_ptr<PositionComponent> positionComponent) {
  this->positionComponent = positionComponent;
}

std::shared_ptr<DrawingComponent> Background::getDrawingComponent() const { return this->drawingComponent; }
void Background::setDrawingComponent(const std::shared_ptr<DrawingComponent> drawingComponent) {
  this->drawingComponent = drawingComponent;
}

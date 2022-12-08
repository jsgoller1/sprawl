#include "Background.hh"

Background::Background(const EntityName entityName, const std::shared_ptr<PositionComponent> positionComponent,
                       const std::shared_ptr<DrawingComponent> drawingComponent)
    : GameObject(entityName, positionComponent, nullptr, nullptr, drawingComponent) {}

Background::~Background() = default;

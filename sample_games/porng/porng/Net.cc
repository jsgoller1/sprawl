#include "Net.hh"

Net::~Net() = default;

Net::Net(const EntityName entityName, const std::shared_ptr<PositionComponent> positionComponent,
         const std::shared_ptr<DrawingComponent> drawingComponent)
    : GameObject(entityName, positionComponent, nullptr, nullptr, drawingComponent) {}

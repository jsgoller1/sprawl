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
             const std::shared_ptr<DrawingComponent> drawingComponent = nullptr);

  std::shared_ptr<PositionComponent> getPositionComponent() const;

  void setPositionComponent(const std::shared_ptr<PositionComponent> positionComponent);

  std::shared_ptr<DrawingComponent> getDrawingComponent() const;
  void setDrawingComponent(const std::shared_ptr<DrawingComponent> drawingComponent);

 private:
  std::shared_ptr<PositionComponent> positionComponent;
  std::shared_ptr<DrawingComponent> drawingComponent;
};

#pragma once

#include "DrawingComponent.hh"
#include "Entity.hh"
#include "GameObject.hh"
#include "PositionComponent.hh"
#include "Texture.hh"
#include "Types.hh"

class Background : public GameObject {
 public:
  Background(const EntityName entityName = EntityName(""),
             const std::shared_ptr<PositionComponent> positionComponent = nullptr,
             const std::shared_ptr<DrawingComponent> drawingComponent = nullptr);
  ~Background() override;
};

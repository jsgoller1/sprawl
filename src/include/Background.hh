#pragma once

#include "DrawingComponent.hh"
#include "PositionComponent.hh"
#include "Screen.hh"
#include "Texture.hh"
#include "Types.hh"

class Background {
 public:
  Background(const shared_ptr<DrawingComponent> drawingComponent,
             const shared_ptr<PositionComponent> positionComponent)
      : drawingComponent(drawingComponent),
        positionComponent(positionComponent) {}

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

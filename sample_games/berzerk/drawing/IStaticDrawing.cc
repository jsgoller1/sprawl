#include "IStaticDrawing.hh"

IStaticDrawing::IStaticDrawing(PositionComponent& positionComponent, const int height, const int width,
                               DrawingProxy& drawingProxy, const std::shared_ptr<Sprite> sprite)
    : IDrawing(positionComponent, height, width, drawingProxy), _sprite(sprite) {}

std::shared_ptr<Sprite> IStaticDrawing::getCurrentSprite() const { return this->_sprite; }

#include "IDrawing.hh"

#include "Vect2D.hh"

IDrawing::~IDrawing() = default;

IDrawing::IDrawing(PositionComponent& positionComponent, const int height, const int width, DrawingProxy& drawingProxy)
    : _positionComponent(positionComponent), _height(height), _width(width), _drawingProxy(drawingProxy) {
  // SDL_SetColorKey(this->_pixelData.get(), SDL_TRUE, SDL_MapRGB(this->_pixelData->format, 0xff, 0xff, 0xff));
}
int IDrawing::getHeight() const { return this->_height; }
int IDrawing::getWidth() const { return this->_width; }

Vect2D IDrawing::getTopLeft() const {
  Vect2D topLeft = this->_positionComponent.getPosition();
  topLeft.x -= this->_width / 2;
  topLeft.y += this->_height / 2;
  return topLeft;
}

DrawingProxy& IDrawing::getDrawingProxy() { return this->_drawingProxy; }

void IDrawing::draw() {
  // TODO: I don't want this method to have any parameters; too complicated for now, but
  // I think when we refactor position code out to IPosition, we can/should create a proxy for it, and anything
  // needing position data can use one.
  this->_drawingProxy.draw(this->_positionComponent.getPosition(), this->_width, this->_height,
                           this->getCurrentSprite());
}

IStaticDrawing::IStaticDrawing(PositionComponent& positionComponent, const int height, const int width,
                               DrawingProxy& drawingProxy, const std::shared_ptr<Sprite> sprite)
    : IDrawing(positionComponent, height, width, drawingProxy), _sprite(sprite) {}

std::shared_ptr<Sprite> IStaticDrawing::getCurrentSprite() { return this->_sprite; }

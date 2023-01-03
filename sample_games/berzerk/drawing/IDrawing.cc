#include "IDrawing.hh"

#include "Vect2D.hh"

IDrawing::IDrawing(PositionComponent& positionComponent, const int height, const int width, DrawingProxy& drawingProxy)
    : _positionComponent(positionComponent), _height(height), _width(width), _drawingProxy(drawingProxy) {
  // SDL_SetColorKey(this->_pixelData.get(), SDL_TRUE, SDL_MapRGB(this->_pixelData->format, 0xff, 0xff, 0xff));
}
IDrawing::~IDrawing() = default;

int IDrawing::getHeight() const { return this->_height; }
int IDrawing::getWidth() const { return this->_width; }

Vect2D IDrawing::getTopLeft() const {
  Vect2D topLeft = this->_positionComponent.getPosition();
  topLeft.x -= this->_width / 2;
  topLeft.y += this->_height / 2;
  return topLeft;
}

DrawingProxy& IDrawing::getDrawingProxy() const { return this->_drawingProxy; }

void IDrawing::draw() {
  this->_drawingProxy.draw(this->_positionComponent.getPosition(), this->_width, this->_height,
                           this->getCurrentSprite());
}

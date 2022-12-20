#include "UIElement.hh"

UIElement::UIElement(const Vect2D& center, const int width, const int height, const std::string& texturePath)
    : Drawable(center, height, width, texturePath) {}

UIElement::~UIElement() = default;

BallsCounter::BallsCounter(const Vect2D& center, const int width, const int height, const std::string& texturePath,
                           const int ballsCount)
    : UIElement(center, height, width, texturePath), _ballsCount(ballsCount) {}

BallsCounter::~BallsCounter() = default;

void BallsCounter::decrement() { this->_ballsCount--; }
int BallsCounter::getBallsCount() const { return this->_ballsCount; }

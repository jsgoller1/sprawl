#include "Ball.hh"

Ball::Ball(const Vect2D& center, const int width, const int height, const std::string& texturePath)
    : Drawable(center, width, height, texturePath) {}

Vect2D Ball::getVelocity() const { return this->_velocity; }
void Ball::setVelocity(const Vect2D& velocity) { this->_velocity = velocity; }

Vect2D Ball::getLeftmostPoint() const { return this->getCenter() - Vect2D(BALL_RADIUS, 0); }
Vect2D Ball::getRightmostPoint() const { return this->getCenter() + Vect2D(BALL_RADIUS, 0); }
Vect2D Ball::getTopPoint() const { return this->getCenter() + Vect2D(0, BALL_RADIUS); }
Vect2D Ball::getBottomPoint() const { return this->getCenter() - Vect2D(0, BALL_RADIUS); }

Ball::~Ball() = default;

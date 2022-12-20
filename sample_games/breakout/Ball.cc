#include "Ball.hh"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

Ball::Ball(const Vect2D& center, const int width, const int height, const std::string& texturePath)
    : Drawable(center, width, height, texturePath) {
  std::srand((unsigned)std::time(nullptr));
}

Vect2D Ball::getVelocity() const { return this->_velocity; }
void Ball::setVelocity(const Vect2D& velocity) { this->_velocity = velocity; }

void Ball::handleHorizontalCollision() {
  Vect2D newVelocity = this->_velocity;
  newVelocity.x *= -1;
  this->_velocity = newVelocity;
}
void Ball::handleVerticalCollision() {
  Vect2D newVelocity = this->_velocity;
  newVelocity.x = 1 + std::rand() % 100;
  newVelocity.x = newVelocity.x * (std::rand() % 2) ? -1 : 1;
  newVelocity.y = newVelocity.y *= -1;
  this->_velocity = newVelocity;
}

Vect2D Ball::getLeftmostPoint() const { return this->getCenter() - Vect2D(BALL_RADIUS, 0); }
Vect2D Ball::getRightmostPoint() const { return this->getCenter() + Vect2D(BALL_RADIUS, 0); }
Vect2D Ball::getTopPoint() const { return this->getCenter() + Vect2D(0, BALL_RADIUS); }
Vect2D Ball::getBottomPoint() const { return this->getCenter() - Vect2D(0, BALL_RADIUS); }

Ball::~Ball() = default;

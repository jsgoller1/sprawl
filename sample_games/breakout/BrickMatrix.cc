#include "BrickMatrix.hh"

#include <iostream>
#include <string>

#include "Ball.hh"
#include "Brick.hh"
#include "Vect2D.hh"

BrickMatrix::BrickMatrix(const Vect2D& topLeft, const int brickWidth, const int brickHeight, const int brickCols,
                         const int brickRows) {
  this->_bricks = std::vector<Brick*>();
  Vect2D center = topLeft;
  center.x += brickWidth / 2;
  center.y -= brickHeight / 2;
  for (int row = 0; row < brickRows; row++) {
    for (int col = 0; col < brickCols; col++) {
      std::string texturePath = std::string(brickColors[(unsigned)row % brickColors.size()]);
      Brick* brick = new Brick(center, brickWidth, brickHeight, texturePath);
      this->_bricks.push_back(brick);
      center.x += (brickWidth + 2);
    }
    center.x = topLeft.x + (brickWidth / 2);
    center.y -= (brickHeight + 2);
  }
}

bool BrickMatrix::empty() { return false; }

std::vector<Brick*>& BrickMatrix::getBricks() { return this->_bricks; }

void BrickMatrix::handleCollisions(const Ball& ball) {
  SDL_Rect ballBox = ball.getBoundingBox();
  SDL_Rect brickBox;
  for (unsigned long i = 0; i < this->_bricks.size(); ++i) {
    Brick* brick = this->_bricks.at(i);
    brickBox = brick->getBoundingBox();
    if (SDL_HasIntersection(&ballBox, &brickBox)) {
      this->_bricks.erase(this->_bricks.begin() + (int)i);
      break;
      //  determine new ball direction : if ball above or below brick, reverse y if ball left or right of brick,
      //      reverse x play collision sound
    }
  }
}

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

void BrickMatrix::erase(Brick* brick) {
  for (unsigned long i = 0; i < this->_bricks.size(); ++i) {
    if (brick == this->_bricks.at(i)) {
      this->_bricks.erase(this->_bricks.begin() + (long)i);
      delete brick;
      return;
    }
  }
}

bool BrickMatrix::empty() { return this->_bricks.empty(); }

std::vector<Brick*>& BrickMatrix::getBricks() { return this->_bricks; }

#include "BrickMatrix.hh"

#include "Vect2D.hh"

BrickMatrix::BrickMatrix(const Vect2D& topLeft, const int brickWidth, const int brickHeight, const int brickCols,
                         const int brickRows) {
  (void)topLeft;
  (void)brickWidth;
  (void)brickHeight;
  (void)brickCols;
  (void)brickRows;
}

bool BrickMatrix::empty() { return false; }

std::vector<Brick*>* BrickMatrix::getBricks() const { return nullptr; }

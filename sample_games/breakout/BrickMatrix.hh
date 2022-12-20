#pragma once

#include <vector>

// Foward decls
class Vect2D;
class Brick;

class BrickMatrix {
 public:
  BrickMatrix(const Vect2D& topLeft, const int brickWidth, const int brickHeight, const int brickCols,
              const int brickRows);
  bool empty();
  std::vector<Brick*>& getBricks();

 private:
  std::vector<Brick*> _bricks;
};

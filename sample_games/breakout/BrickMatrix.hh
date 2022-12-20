#pragma once

#include <SDL2/SDL.h>

#include <vector>

// Foward decls
class Vect2D;
class Brick;
class Ball;

class BrickMatrix {
 public:
  BrickMatrix(const Vect2D& topLeft, const int brickWidth, const int brickHeight, const int brickCols,
              const int brickRows);
  void erase(Brick* brick);
  bool empty();
  std::vector<Brick*>& getBricks();

 private:
  std::vector<Brick*> _bricks;
};

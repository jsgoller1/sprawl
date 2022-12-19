#pragma once

#include "Ball.hh"
#include "BrickMatrix.hh"
#include "Input.hh"
#include "Paddle.hh"
#include "Screen.hh"

enum GameState { LAUNCHING = 0, PLAYING = 1 };

class Game {
 public:
  Game(const int brickCols, const int brickRows);
  ~Game();
  void getInput();
  void update();
  void draw();
  bool shouldQuit();

 private:
  GameState state = LAUNCHING;
  Screen* _screen;
  BrickMatrix* _bricks;
  Paddle* _paddle;
  Ball* _ball;

  Input _input;

  void doCollisions();
  void moveBall();
};

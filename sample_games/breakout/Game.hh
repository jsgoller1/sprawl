#pragma once

#include "Ball.hh"
#include "BrickCollection.hh"
#include "Input.hh"
#include "Paddle.hh"
#include "Screen.hh"

enum GameState { LAUNCHING = 0, PLAYING = 1 };

class Game {
 public:
  Game();
  ~Game();
  void getInput();
  void update();
  void draw();
  bool shouldQuit();

 private:
  Screen* _screen;
  GameState state = LAUNCHING;
  Input _input;
  BrickCollection _bricks;
  Paddle _paddle;
  Ball _ball;

  void doCollisions();
  void moveBall();
};

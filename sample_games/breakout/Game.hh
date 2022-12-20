#pragma once

#include "Ball.hh"
#include "BrickMatrix.hh"
#include "Input.hh"
#include "Paddle.hh"
#include "Screen.hh"
#include "UIElement.hh"

enum GameState { LAUNCHING = 0, PLAYING = 1 };

class Game {
 public:
  Game(const int brickCols = 10, const int brickRows = 6);
  ~Game();
  Vect2D getTopLeft() const;
  Vect2D getTopRight() const;
  Vect2D getBottomLeft() const;
  Vect2D getBottomRight() const;

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
  UIElement* _ballsRemaining;
  BallsCounter* _ballsCounter;

  void doCollisions();
  bool ballHitsCieling() const;
  bool ballHitsWall() const;
  bool ballHitsFloor() const;
  bool ballHitsPaddle() const;
  Brick* ballHitsBrick();

  void handleFloorCollision();
  void handlePaddleCollision() const;
  void handleBrickCollision(Brick* brick);

  void moveBall();
  Vect2D getPaddlePosition();
  bool gameOver();
  void gameOverBehavior();
};

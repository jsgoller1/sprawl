#include "Game.hh"

#include "Ball.hh"
#include "Brick.hh"
#include "BrickMatrix.hh"
#include "Input.hh"
#include "Paddle.hh"
#include "Screen.hh"

Game::Game(const int brickCols, const int brickRows) {
  this->_screen = new Screen();

  Vect2D brickMatrixTopLeft;
  int brickWidth = 0;
  int brickHeight = 0;
  this->_bricks = new BrickMatrix(brickMatrixTopLeft, brickWidth, brickHeight, brickCols, brickRows);

  this->_paddle = new Paddle(PADDLE_START_POSITION, PADDLE_HEIGHT, PADDLE_WIDTH, PADDLE_TEXTURE_PATH);
  this->_ball = new Ball(BALL_START_POSITION, BALL_RADIUS, BALL_RADIUS, BALL_TEXTURE_PATH);
}

Game::~Game() {
  delete this->_screen;
  delete this->_bricks;
  delete this->_paddle;
  delete this->_ball;
}

void Game::getInput() { this->_input = Input(); }

void Game::doCollisions() {
  /*
    if (ball position at either wall) {
      reverse ball x;
    }
    if (ball position at cieling) {
      reverse ball y;
    }
    if (ball position at floor) {
      set state back to launching;
      decrement remaining balls;
    }
    if (ball colliding with brick) {
      remove brick;
      determine new ball direction:
        if ball above or below brick, reverse y
        if ball left or right of brick, reverse x
      play collision sound
    }
    if (ball colliding with paddle) {
      reverse ball y;
      randomize ball x;
      play collision sound
    }
    */
}

void Game::moveBall() {
  if (this->state == LAUNCHING) {
    // Move ball to directly above center of paddle
  } else {
    // Move ball according to its velocity
  }
}

void Game::update() {
  // this->_paddle.move();
  this->moveBall();
  this->doCollisions();
}

void Game::draw() {
  this->_screen->clear();

  // TODO: Implement some kind of "DrawData" struct to make this API opaque
  this->_screen->prepare(this->_paddle->getCenter(), this->_paddle->getHeight(), this->_paddle->getWidth(),
                         this->_paddle->getPixelData());
  this->_screen->prepare(this->_ball->getCenter(), this->_ball->getHeight(), this->_ball->getWidth(),
                         this->_ball->getPixelData());

  /*
  std::vector<Brick *> *bricks = this->_bricks->getBricks();
  for (Brick *brick : *bricks) {
    this->_screen->prepare(brick->getCenter(), brick->getHeight(), brick->getWidth(), brick->getPixelData());
  }
  delete bricks;
  */
  this->_screen->draw();
}

bool Game::shouldQuit() {
  // If this->input is SDL_QUIT or escape
  return this->_bricks->empty();
}

#include "Game.hh"

#include "Ball.hh"
#include "BrickCollection.hh"
#include "Input.hh"
#include "Paddle.hh"
#include "Screen.hh"

Game::Game() {
  this->_screen = new Screen();
  this->_bricks = BrickCollection();
  this->_paddle = Paddle();
  this->_ball = Ball();
}

Game::~Game() { delete this->_screen; }

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
  this->_paddle.move();
  this->moveBall();
  this->doCollisions();
}

void Game::draw() {
  // clear current screen
  // prepare paddle
  // prepare ball
  // for brick in brick collection, prepare brick
  // draw current screen
}

bool Game::shouldQuit() { return this->_bricks.empty(); }

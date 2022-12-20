#include "Game.hh"

#include "Ball.hh"
#include "Brick.hh"
#include "BrickMatrix.hh"
#include "Input.hh"
#include "Paddle.hh"
#include "Screen.hh"

Game::Game(const int brickCols, const int brickRows) {
  // 100 px for each brick, plus 1px of space between each
  int screenWidth = (brickCols * BRICK_WIDTH) + brickCols;
  // Roughly 3x the amount of vertical space needed
  int screenHeight = brickRows * BRICK_HEIGHT * 3;
  this->_screen = new Screen(screenWidth, screenHeight);

  Vect2D brickMatrixTopLeft{.x = -(screenWidth / 2), .y = screenHeight / 2};
  this->_bricks = new BrickMatrix(brickMatrixTopLeft, BRICK_WIDTH, BRICK_HEIGHT, brickCols, brickRows);

  this->_paddle = new Paddle(Vect2D{0, 0}, PADDLE_HEIGHT, PADDLE_WIDTH, PADDLE_TEXTURE_PATH);
  this->_ball = new Ball(Vect2D{0, 0}, BALL_RADIUS, BALL_RADIUS, BALL_TEXTURE_PATH);
  this->_input = Input();
}

Game::~Game() {
  delete this->_screen;
  delete this->_bricks;
  delete this->_paddle;
  delete this->_ball;
}

void Game::getInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    switch (event.type) {
      case SDL_MOUSEMOTION:
        this->_input.mousePos = Vect2D{.x = event.motion.x, .y = event.motion.y};
        break;
      case SDL_QUIT:
        this->_input.shouldQuit = true;
        break;
      default:
        break;
    }
  }
}

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
    Vect2D ballPosition = this->getPaddlePosition();
    ballPosition.y += BALL_RADIUS;
    this->_ball->setCenter(ballPosition);
  } else {
    // Move ball according to its velocity
  }
}

Vect2D Game::getPaddlePosition() {
  Vect2D paddleCenter = this->_screen->toWorldCoordinates(this->_input.mousePos);
  paddleCenter.y = this->_screen->getHeight() / 2 * -1 + PADDLE_HEIGHT + 2;
  return paddleCenter;
}

void Game::update() {
  this->_paddle->setCenter(this->getPaddlePosition());
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

  std::vector<Brick *> bricks = this->_bricks->getBricks();
  for (Brick *brick : bricks) {
    this->_screen->prepare(brick->getCenter(), brick->getHeight(), brick->getWidth(), brick->getPixelData());
  }
  this->_screen->draw();
}

bool Game::shouldQuit() {
  // If this->input is SDL_QUIT or escape
  return this->_bricks->empty() || this->_input.shouldQuit == true;
}

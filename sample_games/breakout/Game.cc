#include "Game.hh"

#include <iostream>

#include "Ball.hh"
#include "Brick.hh"
#include "BrickMatrix.hh"
#include "Input.hh"
#include "Paddle.hh"
#include "Screen.hh"
#include "UIElement.hh"

Game::Game(const int brickCols, const int brickRows) {
  // 100 px for each brick, plus 1px of space between each
  int screenWidth = (brickCols * BRICK_WIDTH) + brickCols;
  // Roughly 3x the amount of vertical space needed
  int screenHeight = brickRows * BRICK_HEIGHT * 3;
  this->_screen = new Screen(screenWidth, screenHeight);
  this->_bricks = new BrickMatrix(this->getTopLeft(), BRICK_WIDTH, BRICK_HEIGHT, brickCols, brickRows);
  this->_paddle = new Paddle(Vect2D{0, 0}, PADDLE_HEIGHT, PADDLE_WIDTH, PADDLE_TEXTURE_PATH);
  this->_ball = new Ball(Vect2D{0, 0}, BALL_RADIUS, BALL_RADIUS, BALL_TEXTURE_PATH);
  this->_ballsRemaining =
      new UIElement(Vect2D(-screenWidth / 2 + 150, -screenWidth / 2 + 50), 320, 50, BALLS_REMAINING_TEXTURE_PATH);
  this->_ballsCounter =
      new BallsCounter(Vect2D(-screenWidth / 2 + 100, -screenWidth / 2 + 50), 50, 50, BALLS_COUNT_3_TEXTURE_PATH, 3);
  this->_input = Input();
  this->state = LAUNCHING;
}

Game::~Game() {
  delete this->_screen;
  delete this->_bricks;
  delete this->_paddle;
  delete this->_ball;
}

Vect2D Game::getTopLeft() const { return this->_screen->toWorldCoordinates(this->_screen->getTopLeft()); }
Vect2D Game::getTopRight() const { return this->_screen->toWorldCoordinates(this->_screen->getTopRight()); }
Vect2D Game::getBottomLeft() const { return this->_screen->toWorldCoordinates(this->_screen->getBottomLeft()); }
Vect2D Game::getBottomRight() const { return this->_screen->toWorldCoordinates(this->_screen->getBottomRight()); }

void Game::getInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    switch (event.type) {
      case SDL_MOUSEBUTTONDOWN:
        this->_input.buttonPressed = true;
        std::cout << event.button.x << "," << event.button.y << std::endl;
        break;
      case SDL_MOUSEMOTION:
        this->_input.mousePos = Vect2D(event.motion.x, event.motion.y);
        break;
      case SDL_QUIT:
        this->_input.shouldQuit = true;
        break;
      default:
        break;
    }
  }
}
void Game::update() {
  if (this->gameOver()) {
    this->gameOverBehavior();
    return;
  }

  if (this->_input.buttonPressed) {
    this->state = PLAYING;
    this->_input.buttonPressed = false;
  }

  this->_paddle->setCenter(this->getPaddlePosition());
  this->moveBall();
  this->doCollisions();
}
void Game::draw() {
  this->_screen->clear();

  this->_screen->prepare(this->_ballsRemaining->getCenter(), this->_ballsRemaining->getHeight(),
                         this->_ballsRemaining->getWidth(), this->_ballsRemaining->getPixelData());
  this->_screen->prepare(this->_ballsCounter->getCenter(), this->_ballsCounter->getHeight(),
                         this->_ballsCounter->getWidth(), this->_ballsCounter->getPixelData());
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
  return this->_input.shouldQuit == true;
}

void Game::doCollisions() {
  if (this->ballHitsWall()) {
    this->_ball->handleHorizontalCollision();
  }

  if (this->ballHitsCieling()) {
    this->_ball->handleVerticalCollision();
  }

  if (this->ballHitsFloor()) {
    this->handleFloorCollision();
  }

  if (ballHitsPaddle()) {
    this->handlePaddleCollision();
  }

  Brick *collidingBrick = this->ballHitsBrick();
  if (collidingBrick != nullptr) {
    this->handleBrickCollision(collidingBrick);
  }
}
bool Game::ballHitsCieling() const { return this->_ball->getTopPoint().above(this->getTopLeft()); }
bool Game::ballHitsWall() const {
  return this->_ball->getLeftmostPoint().left(this->getBottomLeft()) ||
         this->_ball->getRightmostPoint().right(this->getBottomRight());
}
bool Game::ballHitsFloor() const { return this->_ball->getBottomPoint().below(this->getBottomRight()); }
bool Game::ballHitsPaddle() const {
  SDL_Rect ballBox = this->_ball->getBoundingBox(), paddleBox = this->_paddle->getBoundingBox();
  return SDL_HasIntersection(&ballBox, &paddleBox);
}
Brick *Game::ballHitsBrick() {
  SDL_Rect ballBox = this->_ball->getBoundingBox();
  SDL_Rect brickBox;
  std::vector<Brick *> bricks = this->_bricks->getBricks();

  for (unsigned long i = 0; i < bricks.size(); ++i) {
    Brick *brick = bricks.at(i);
    brickBox = brick->getBoundingBox();
    if (SDL_HasIntersection(&ballBox, &brickBox)) {
      return brick;
    }
  }
  return nullptr;
}

void Game::handleFloorCollision() {
  this->state = LAUNCHING;
  this->_ball->setVelocity(Vect2D(0, 10));
  this->_ballsCounter->decrement();
}
void Game::handlePaddleCollision() const {
  Vect2D newVelocity = this->_ball->getVelocity();
  // The ball's horizontal movement becomes more severe the closer to the edge of the paddle it hits
  Vect2D paddleCenter = this->_paddle->getCenter(), ballCenter = this->_ball->getCenter();

  newVelocity.y *= -1;
  newVelocity.x = int((ballCenter.x - paddleCenter.x) / 2);
  this->_ball->setVelocity(newVelocity);
}
void Game::handleBrickCollision(Brick *brick) {
  // If the ball's center falls within the brick's width, it must be a
  // vertical strike; otherwise, it is a horizontal / side strike
  Vect2D ballCenter = this->_ball->getCenter(), brickBottomLeft = brick->getBottomLeft(),
         brickBottomRight = brick->getBottomRight();
  if (brickBottomLeft.left(ballCenter) && brickBottomRight.right(ballCenter)) {
    this->_ball->handleVerticalCollision();
  } else
    // The ball hit the brick from the sides
    this->_ball->handleHorizontalCollision();
  this->_bricks->erase(brick);
}

void Game::moveBall() {
  if (this->state == LAUNCHING) {
    // Move ball to directly above center of paddle
    Vect2D ballPosition = this->getPaddlePosition();
    ballPosition.y += BALL_RADIUS;
    this->_ball->setCenter(ballPosition);
  } else {
    this->_ball->updateCenter(this->_ball->getVelocity());
  }
}
Vect2D Game::getPaddlePosition() {
  Vect2D paddleCenter = this->_screen->toWorldCoordinates(this->_input.mousePos);
  paddleCenter.y = this->_screen->getHeight() / 2 * -1 + PADDLE_HEIGHT + 2;
  return paddleCenter;
}
bool Game::gameOver() { return this->_bricks->empty() || this->_ballsCounter->getBallsCount() <= 0; }
void Game::gameOverBehavior() {}

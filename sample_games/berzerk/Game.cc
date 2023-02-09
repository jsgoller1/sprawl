#include "Game.hh"

#include <iostream>

#include "BulletSpriteManager.hh"
#include "CLI.hh"
#include "DrawingProxy.hh"
#include "InputHandler.hh"
#include "LevelSpriteManager.hh"
#include "OttoSpriteManager.hh"
#include "PlayerSpriteManager.hh"
#include "RobotSpriteManager.hh"
#include "Screen.hh"
#include "TextSpriteManager.hh"
#include "UI.hh"

// Public
Game::Game(const CLI& args, Screen& screen, InputHandler& inputHandler, Timer& timer)
    : _levelSpriteManager(std::unique_ptr<LevelSpriteManager>(new LevelSpriteManager(args.getLevelSpriteSheetPath()))),
      _playerSpriteManager(
          std::unique_ptr<PlayerSpriteManager>(new PlayerSpriteManager(args.getPlayerSpriteSheetPath()))),
      _robotSpriteManager(std::unique_ptr<RobotSpriteManager>(new RobotSpriteManager(args.getRobotSpriteSheetPath()))),
      _ottoSpriteManager(std::unique_ptr<OttoSpriteManager>(new OttoSpriteManager(args.getOttoSpriteSheetPath()))),
      _bulletSpriteManager(
          std::unique_ptr<BulletSpriteManager>(new BulletSpriteManager(args.getBulletSpriteSheetPath()))),
      _textSpriteManager(std::unique_ptr<TextSpriteManager>(new TextSpriteManager(args.getTextSpriteSheetPath()))),
      _inputHandler(inputHandler),
      _screen(screen),
      _timer(timer) {
  this->_ui =
      std::make_unique<UI>(*this->_textSpriteManager, this->_screen.getScreenDrawingProxy(), this->_LevelDataProxy);
  this->_currentLevel = std::make_unique<Level>(
      this->_levelNo, this->_LevelDataProxy, this->_screen.getScreenDrawingProxy(), *this->_levelSpriteManager,
      *this->_playerSpriteManager, *this->_robotSpriteManager, *this->_bulletSpriteManager, *this->_ottoSpriteManager);
}

void Game::run() {
  /*
  Core game loop
  */
  while (!(this->isLost() || this->_inputHandler.shouldQuit())) {
    this->_timer.tick();
    this->_inputHandler.getKeyboardInput();
    this->update(this->_inputHandler, this->_timer.getProxy());
    this->draw(this->_screen);
  }
}

void Game::update(const InputHandler& inputHandler, const TimerProxy& timerProxy) {
  if (this->_isPaused) {
    return;
  }
  if (this->_currentLevel->isFinished()) {
    if (!this->_currentLevel->playerAtExit()) {
      // If player is dead, decrement life counter and create new level
      this->_playerLives--;
    }
    this->_levelNo = this->_playerScore / SCORE_LEVEL_THRESHOLD;
    this->_currentLevel =
        std::make_unique<Level>(this->_levelNo, this->_LevelDataProxy, this->_screen.getScreenDrawingProxy(),
                                *this->_levelSpriteManager, *this->_playerSpriteManager, *this->_robotSpriteManager,
                                *this->_bulletSpriteManager, *this->_ottoSpriteManager);
    this->_timer.reset();
  }
  this->_ui->update();
  this->_currentLevel->update(inputHandler, timerProxy);
}

void Game::draw(Screen& screen) {
  screen.clear();
  this->_ui->draw();
  this->_currentLevel->draw();
  screen.render();
}

// Private
void Game::initUI(const TextSpriteManager& textSpriteManager, DrawingProxy& drawingProxy) {
  // The UI (lives remaining and score) should take up
  // the bottom 10% of the screen or less

  (void)textSpriteManager;
  (void)drawingProxy;
}

bool Game::isLost() { return this->_playerLives <= 0; }

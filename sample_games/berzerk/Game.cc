#include "Game.hh"

#include <iostream>

#include "CLI.hh"
#include "InputHandler.hh"
#include "Screen.hh"

Game::Game(Screen& screen, InputHandler& inputHandler, const CLI& args)
    : _screen(screen),
      _inputHandler(inputHandler),
      _levelSpriteManager(std::unique_ptr<LevelSpriteManager>(new LevelSpriteManager(args.getLevelSpriteSheetPath()))),
      _playerSpriteManager(
          std::unique_ptr<PlayerSpriteManager>(new PlayerSpriteManager(args.getCharacterSpriteSheetPath()))),
      _robotSpriteManager(
          std::unique_ptr<RobotSpriteManager>(new RobotSpriteManager(args.getCharacterSpriteSheetPath()))),
      _textSpriteManager(std::unique_ptr<TextSpriteManager>(new TextSpriteManager(args.getTextSpriteSheetPath()))) {
  this->initUI();
  this->_currentLevel = std::unique_ptr<Level>(new Level(this->_screen.getScreenDrawingProxy(),
                                                         *this->_levelSpriteManager, *this->_playerSpriteManager,
                                                         *this->_robotSpriteManager, *this->_textSpriteManager));
}

// Public

bool Game::getShouldQuit() const { return this->_shouldQuit; }

void Game::getInput() {
  this->_inputHandler.getKeyboardInput();
  if (this->_inputHandler.escapePressed() || this->_inputHandler.gotSDLQuit()) {
    this->_shouldQuit = true;
  }
}

void Game::update() { this->updateLoseConditions(); }

void Game::draw() const {
  this->_screen.clear();
  this->_screen.drawAll();
}

// Private

void Game::initUI() {
  // The UI (lives remaining and score) should take up
  // the bottom 10% of the screen or less
}

void Game::updateLoseConditions() {
  if (this->playerLives <= 0) {
    this->_shouldQuit = true;
  }
}

#include "Game.hh"

#include <iostream>

#include "BulletSpriteManager.hh"
#include "CLI.hh"
#include "DrawingProxy.hh"
#include "InputHandler.hh"
#include "LevelSpriteManager.hh"
#include "PlayerSpriteManager.hh"
#include "RobotSpriteManager.hh"
#include "Screen.hh"
#include "TextSpriteManager.hh"

// Public
Game::Game(const CLI& args, DrawingProxy& drawingProxy)
    : _levelSpriteManager(std::unique_ptr<LevelSpriteManager>(new LevelSpriteManager(args.getLevelSpriteSheetPath()))),
      _playerSpriteManager(
          std::unique_ptr<PlayerSpriteManager>(new PlayerSpriteManager(args.getCharacterSpriteSheetPath()))),
      _robotSpriteManager(
          std::unique_ptr<RobotSpriteManager>(new RobotSpriteManager(args.getCharacterSpriteSheetPath()))),
      _textSpriteManager(std::unique_ptr<TextSpriteManager>(new TextSpriteManager(args.getTextSpriteSheetPath()))),
      _bulletSpriteManager(
          std::unique_ptr<BulletSpriteManager>(new BulletSpriteManager(args.getBulletSpriteSheetPath()))) {
  this->initUI(*this->_textSpriteManager, drawingProxy);
  this->_currentLevel =
      std::unique_ptr<Level>(new Level(drawingProxy, *this->_levelSpriteManager, *this->_playerSpriteManager,
                                       *this->_robotSpriteManager, *this->_bulletSpriteManager));
}

bool Game::getShouldQuit() const { return this->_shouldQuit; }

void Game::update(const InputHandler& inputHandler, const time_ms deltaT) {
  this->updateLoseConditions();
  _currentLevel->update(inputHandler, deltaT);
}

void Game::draw(Screen& screen) {
  screen.clear();
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

void Game::updateLoseConditions() {
  if (this->playerLives <= 0) {
    this->_shouldQuit = true;
  }
}

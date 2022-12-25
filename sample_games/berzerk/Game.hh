#pragma once
#include <memory>

#include "Level.hh"
#include "SpriteManager.hh"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

// fwd decls
class CLI;
class InputHandler;
class Screen;

class Game {
 public:
  Game(Screen& screen, InputHandler& inputHandler, const CLI& args);

  bool getShouldQuit() const;
  void getInput();
  void update();
  void draw() const;

 private:
  Screen& _screen;
  InputHandler& _inputHandler;
  std::unique_ptr<Level> _currentLevel;

  std::unique_ptr<LevelSpriteManager> _levelSpriteManager;
  std::unique_ptr<PlayerSpriteManager> _playerSpriteManager;
  std::unique_ptr<RobotSpriteManager> _robotSpriteManager;
  std::unique_ptr<TextSpriteManager> _textSpriteManager;

  bool _shouldQuit = false;
  int playerLives = 3;

  void initUI();
  void updateLoseConditions();
};

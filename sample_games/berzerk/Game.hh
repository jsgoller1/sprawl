#pragma once
#include <memory>

#include "Level.hh"
#include "SpriteManager.hh"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

// fwd decls
class CLI;
class DrawingProxy;
class InputHandler;
class Screen;

class Game {
 public:
  Game(const CLI& args, DrawingProxy& drawingProxy);

  bool getShouldQuit() const;
  void update(const InputHandler& inputHandler);
  void draw(Screen& screen);

 private:
  std::unique_ptr<Level> _currentLevel;

  std::unique_ptr<LevelSpriteManager> _levelSpriteManager;
  std::unique_ptr<PlayerSpriteManager> _playerSpriteManager;
  std::unique_ptr<RobotSpriteManager> _robotSpriteManager;
  std::unique_ptr<TextSpriteManager> _textSpriteManager;

  bool _shouldQuit = false;
  int playerLives = 3;

  void initUI(const TextSpriteManager& textSpriteManager, DrawingProxy& drawingProxy);
  void updateLoseConditions();
};

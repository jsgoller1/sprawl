#pragma once
#include <memory>

#include "BulletSpriteManager.hh"
#include "Level.hh"
#include "LevelSpriteManager.hh"
#include "OttoSpriteManager.hh"
#include "PlayerSpriteManager.hh"
#include "RobotSpriteManager.hh"
#include "ScoreProxy.hh"
#include "TextSpriteManager.hh"
#include "Time.hh"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

// fwd decls
class CLI;
class DrawingProxy;
class InputHandler;
class Screen;

class Game {
 public:
  Game(const CLI& args, Screen& screen, InputHandler& inputHandler, Timer& timer);
  void run();

  bool getShouldQuit() const;
  void update(const InputHandler& inputHandler, const time_ms delta_t);
  void draw(Screen& screen);

 private:
  std::unique_ptr<Level> _currentLevel;
  std::unique_ptr<LevelSpriteManager> _levelSpriteManager;
  std::unique_ptr<PlayerSpriteManager> _playerSpriteManager;
  std::unique_ptr<RobotSpriteManager> _robotSpriteManager;
  std::unique_ptr<OttoSpriteManager> _ottoSpriteManager;
  std::unique_ptr<BulletSpriteManager> _bulletSpriteManager;
  std::unique_ptr<TextSpriteManager> _textSpriteManager;
  InputHandler& _inputHandler;
  Screen& _screen;
  Timer& _timer;

  bool _isPaused = false;
  int _playerLives = 1;
  int _playerScore = 0;
  int _levelNo = 0;
  ScoreProxy _scoreProxy = ScoreProxy(&this->_playerScore);

  void initUI(const TextSpriteManager& textSpriteManager, DrawingProxy& drawingProxy);
  bool isLost();
};

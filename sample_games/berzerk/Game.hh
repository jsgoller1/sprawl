#pragma once

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

// fwd decls
class Robot;
class Screen;
class Input;

class Game {
 public:
  Game();
  ~Game();

  void initUI();
  bool getShouldQuit() const;

  // Core game loop functions
  void getInput();
  void updateLoseConditions();
  void updateAnimations();
  void updateAI();
  void updateCollisions();
  void moveCharacters();
  void draw() const;

 private:
  bool _shouldQuit = false;
  int playerLives = 3;
  Screen* _screen;
  Input* _input;

  // owns: currentLevel
};

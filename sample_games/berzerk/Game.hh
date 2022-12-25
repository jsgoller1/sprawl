#pragma once

// fwd decls
class Robot;

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
  bool shouldQuit = false;
  int playerLives = 3;
  // owns: currentLevel
};

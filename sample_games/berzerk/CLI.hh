#pragma once

#include <string>

// TODO: Currently, the CLI doesn't even use the given input and just uses these, but these will later be overridable
// defaults
#define DEFAULT_LEVEL_SPRITE_SHEET_PATH "/Users/joshua/Code/sprawl/sample_games/berzerk/assets/level-sprites.png"
#define DEFAULT_PLAYER_SPRITE_SHEET_PATH "/Users/joshua/Code/sprawl/sample_games/berzerk/assets/player-sprites.png"
#define DEFAULT_ROBOT_SPRITE_SHEET_PATH "/Users/joshua/Code/sprawl/sample_games/berzerk/assets/robot-sprites.png"
#define DEFAULT_OTTO_SPRITE_SHEET_PATH "/Users/joshua/Code/sprawl/sample_games/berzerk/assets/otto-sprites.png"
#define DEFAULT_BULLET_SPRITE_SHEET_PATH "/Users/joshua/Code/sprawl/sample_games/berzerk/assets/bullet-sprites.png"
#define DEFAULT_TEXT_SPRITE_SHEET_PATH "/Users/joshua/Code/sprawl/sample_games/berzerk/assets/text-sprites.png"

class CLI {
 public:
  CLI(const int argc, const char* const argv[]);
  bool shouldQuit() const;
  int getReturnCode() const;

  const std::string& getLevelSpriteSheetPath() const;
  const std::string& getPlayerSpriteSheetPath() const;
  const std::string& getRobotSpriteSheetPath() const;
  const std::string& getOttoSpriteSheetPath() const;
  const std::string& getBulletSpriteSheetPath() const;
  const std::string& getTextSpriteSheetPath() const;

 private:
  bool _quit;
  int _returnCode;
  std::string _levelSpriteSheetPath;
  std::string _playerSpriteSheetPath;
  std::string _robotSpriteSheetPath;
  std::string _ottoSpriteSheetPath;
  std::string _bulletSpriteSheetPath;
  std::string _textSpriteSheetPath;

  bool argsCountValid(const int argc) const;
  bool confirmFileExists(const char* const path);
  bool shouldShowHelp(const int argc, const char* const argv[]) const;
  void suggestHelp() const;
  void showHelp() const;
};

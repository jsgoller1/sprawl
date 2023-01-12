#pragma once

#include <string>

#define DEFAULT_LEVEL_SPRITE_SHEET_PATH "/home/joshua/Code/sprawl/sample_games/berzerk/assets/level-sprites.png"
#define DEFAULT_CHARACTER_SPRITE_SHEET_PATH "/home/joshua/Code/sprawl/sample_games/berzerk/assets/character-sprites.png"
#define DEFAULT_TEXT_SPRITE_SHEET_PATH "/home/joshua/Code/sprawl/sample_games/berzerk/assets/text-sprites.png"
#define DEFAULT_BULLET_SPRITE_SHEET_PATH "/home/joshua/Code/sprawl/sample_games/berzerk/assets/bullet-sprites.png"

class CLI {
 public:
  CLI(const int argc, const char* const argv[]);
  bool shouldQuit() const;
  int getReturnCode() const;

  const std::string& getLevelSpriteSheetPath() const;
  const std::string& getCharacterSpriteSheetPath() const;
  const std::string& getTextSpriteSheetPath() const;
  const std::string& getBulletSpriteSheetPath() const;

 private:
  bool _quit;
  int _returnCode;
  std::string _levelSpriteSheetPath;
  std::string _characterSpriteSheetPath;
  std::string _textSpriteSheetPath;
  std::string _bulletSpriteSheetPath;

  bool argsCountValid(const int argc) const;
  bool confirmFileExists(const char* const path);
  bool shouldShowHelp(const int argc, const char* const argv[]) const;
  void suggestHelp() const;
  void showHelp() const;
};

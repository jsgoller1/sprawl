#pragma once

#include <string>

#define DEFAULT_LEVEL_SPRITE_SHEET_PATH "/home/joshua/Code/sprawl/sample_games/berzerk/textures/level-sprites.png"
#define DEFAULT_CHARACTER_SPRITE_SHEET_PATH \
  "/home/joshua/Code/sprawl/sample_games/berzerk/textures/character-sprites.png"
#define DEFAULT_TEXT_SPRITE_SHEET_PATH "/home/joshua/Code/sprawl/sample_games/berzerk/textures/text-sprites.png"

class CLI {
 public:
  CLI(const int argc, const char* const argv[]);
  bool shouldQuit() const;
  int getReturnCode() const;

  const std::string& getLevelSpriteSheetPath() const;
  const std::string& getCharacterSpriteSheetPath() const;
  const std::string& getTextSpriteSheetPath() const;

 private:
  bool _quit;
  int _returnCode;
  std::string _levelSpriteSheetPath;
  std::string _characterSpriteSheetPath;
  std::string _textSpriteSheetPath;

  bool argsCountValid(const int argc) const;
  bool confirmFileExists(const char* const path);
  bool shouldShowHelp(const int argc, const char* const argv[]) const;
  void suggestHelp() const;
  void showHelp() const;
};

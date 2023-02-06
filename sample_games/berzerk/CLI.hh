#pragma once

#include <string>

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
  bool _quit = false;
  int _returnCode = 0;
  std::string _assetsDirPath;
  std::string _levelSpriteSheetPath;
  std::string _playerSpriteSheetPath;
  std::string _robotSpriteSheetPath;
  std::string _ottoSpriteSheetPath;
  std::string _bulletSpriteSheetPath;
  std::string _textSpriteSheetPath;

  bool confirmFileExists(const char* const path);
  bool shouldShowHelp(const int argc, const char* const argv[]) const;
  void suggestHelp() const;
  void showHelp() const;
};

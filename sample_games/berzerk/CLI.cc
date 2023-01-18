#include "CLI.hh"

#include <iostream>

#include "SDL2/SDL.h"

CLI::CLI(const int argc, const char* const argv[]) {
  if (!argsCountValid(argc)) {
    this->suggestHelp();
    this->_returnCode = -1;
    this->_quit = true;
    return;
  }
  if (shouldShowHelp(argc, argv)) {
    this->showHelp();
    this->_returnCode = 0;
    this->_quit = true;
    return;
  }
  bool allFilesExist = true;
  for (int i = 0; i < argc; i++) {
    allFilesExist = confirmFileExists(argv[0]);
  }
  if (not allFilesExist) {
    this->_returnCode = -1;
    this->_quit = true;
  }

  // TODO: just a hack for now
  //   this->_levelSpriteSheetPath = std::string(argv[1]);
  //   this->_characterSpriteSheetPath = std::string(argv[2]);
  //   this->_textSpriteSheetPath = std::string(argv[3]);
  this->_levelSpriteSheetPath = std::string(DEFAULT_LEVEL_SPRITE_SHEET_PATH);
  this->_playerSpriteSheetPath = std::string(DEFAULT_PLAYER_SPRITE_SHEET_PATH);
  this->_robotSpriteSheetPath = std::string(DEFAULT_ROBOT_SPRITE_SHEET_PATH);
  this->_ottoSpriteSheetPath = std::string(DEFAULT_OTTO_SPRITE_SHEET_PATH);
  this->_bulletSpriteSheetPath = std::string(DEFAULT_BULLET_SPRITE_SHEET_PATH);
  this->_textSpriteSheetPath = std::string(DEFAULT_TEXT_SPRITE_SHEET_PATH);
}

int CLI::getReturnCode() const { return this->_returnCode; }
bool CLI::shouldQuit() const { return this->_quit; }
const std::string& CLI::getLevelSpriteSheetPath() const { return this->_levelSpriteSheetPath; }
const std::string& CLI::getPlayerSpriteSheetPath() const { return this->_playerSpriteSheetPath; }
const std::string& CLI::getRobotSpriteSheetPath() const { return this->_robotSpriteSheetPath; }
const std::string& CLI::getOttoSpriteSheetPath() const { return this->_ottoSpriteSheetPath; }
const std::string& CLI::getBulletSpriteSheetPath() const { return this->_bulletSpriteSheetPath; }
const std::string& CLI::getTextSpriteSheetPath() const { return this->_textSpriteSheetPath; }

// Private
bool CLI::argsCountValid(const int argc) const {
  if (argc > 5) {
    std::cout << "berzerk: Too many args provided." << std::endl;
    return false;
  }
  if (argc < 4) {
    std::cout << "berzerk: Too few args provided." << std::endl;
    return false;
  }
  return true;
}

bool CLI::confirmFileExists(const char* const path) {
  // TODO: Is there any other way to do a platform-independent stat? SDL doesn't seem to have one.
  // TODO: This is not platform independent and will break on non-POSIX systems; we can use Boost for
  // portable FS operations
  bool valid = true;
  SDL_RWops* ops = SDL_RWFromFile(path, "r");
  if (ops == nullptr) {
    std::cout << "berzerk: cannot find " << std::string(path) << std::endl;
    valid = false;
  }
  SDL_RWclose(ops);
  return valid;
}

bool CLI::shouldShowHelp(const int argc, const char* const argv[]) const {
  std::string argstring;
  for (int i = 0; i < argc; i++) {
    argstring = std::string(argv[i]);
    if (argstring == "-h" || argstring == "--help") {
      return true;
    }
  }
  return false;
}

void CLI::showHelp() const {
  std::cout << "Usage: berzerk spritefile1 spritefile2 spritefile3 " << std::endl;
  std::cout << "      --help     display this help and exit" << std::endl;
}

void CLI::suggestHelp() const { std::cout << "Try 'berzerk --help' for more information." << std::endl; }

#include "CLI.hh"

#include <iostream>

#include "Configs.hh"
#include "SDL2/SDL.h"

CLI::CLI(const int argc, const char* const argv[]) {
  if (argc != 2) {
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

  this->_assetsDirPath = std::string(argv[1]);
  if (not confirmFileExists(argv[1])) {
    std::cout << "Error, quitting! Could not find assets directory at " << this->_assetsDirPath << std::endl;
    this->_returnCode = -1;
    this->_quit = true;
  }

  // NOTE: Not going to bother checking if these exist; going to assume if the directory exists, it hasn't been
  // modified and the sprite sheets exists.
  this->_levelSpriteSheetPath = this->_assetsDirPath + std::string(DEFAULT_LEVEL_SPRITE_SHEET_PATH);
  this->_playerSpriteSheetPath = this->_assetsDirPath + std::string(DEFAULT_PLAYER_SPRITE_SHEET_PATH);
  this->_robotSpriteSheetPath = this->_assetsDirPath + std::string(DEFAULT_ROBOT_SPRITE_SHEET_PATH);
  this->_ottoSpriteSheetPath = this->_assetsDirPath + std::string(DEFAULT_OTTO_SPRITE_SHEET_PATH);
  this->_bulletSpriteSheetPath = this->_assetsDirPath + std::string(DEFAULT_BULLET_SPRITE_SHEET_PATH);
  this->_textSpriteSheetPath = this->_assetsDirPath + std::string(DEFAULT_TEXT_SPRITE_SHEET_PATH);
}

int CLI::getReturnCode() const { return this->_returnCode; }
bool CLI::shouldQuit() const { return this->_quit; }
const std::string& CLI::getLevelSpriteSheetPath() const { return this->_levelSpriteSheetPath; }
const std::string& CLI::getPlayerSpriteSheetPath() const { return this->_playerSpriteSheetPath; }
const std::string& CLI::getRobotSpriteSheetPath() const { return this->_robotSpriteSheetPath; }
const std::string& CLI::getOttoSpriteSheetPath() const { return this->_ottoSpriteSheetPath; }
const std::string& CLI::getBulletSpriteSheetPath() const { return this->_bulletSpriteSheetPath; }
const std::string& CLI::getTextSpriteSheetPath() const { return this->_textSpriteSheetPath; }

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
  std::cout << "Usage: berzerk <path to assets directory> " << std::endl;
  std::cout << "      --help     display this help and exit" << std::endl;
}

void CLI::suggestHelp() const { std::cout << "Try 'berzerk --help' for more information." << std::endl; }

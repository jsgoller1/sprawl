#include "CLI.hh"

#include "SDL2/SDL.h"

CLI::CLI(const int argc, const char* const argv[]) {
  if (argc > 2) {
    cout << "sprawl: Too many args provided." << endl;
    this->suggestHelp();
    this->_returnCode = -1;
    this->_quit = true;
    return;
  }
  if (argc < 2) {
    cout << "sprawl: No WAD directory provided." << endl;
    this->suggestHelp();
    this->_returnCode = -1;
    this->_quit = true;
    return;
  }

  string argstring = string(argv[1]);
  if (argstring == "-h" || argstring == "--help") {
    this->showHelp();
    this->_returnCode = 0;
    this->_quit = true;
    return;
  }

  // TODO: Is there any other way to do a platform-independent stat? SDL doesn't seem to have one.
  // TODO: This is not platform independent and will break on non-POSIX systems; we can use Boost for
  // portable FS operations
  this->_wadDir = string(argv[1]);
  SDL_RWops* ops = SDL_RWFromFile(this->getWADpath().c_str(), "r");
  if (ops == nullptr) {
    cout << "sprawl: cannot find " << this->getWADpath() << endl;
    this->suggestHelp();
    this->_returnCode = -1;
    this->_quit = true;
    return;
  }
  SDL_RWclose(ops);
  this->_returnCode = 0;
  this->_quit = false;
}

int CLI::getReturnCode() const { return this->_returnCode; }

bool CLI::shouldQuit() const { return this->_quit; }

string CLI::getWADpath() const { return this->_wadDir + "/wad.json"; }
string CLI::getWADDir() const { return this->_wadDir; }

void CLI::showHelp() {
  cout << "Usage: sprawl WAD_DIRECTORY " << endl;
  cout << "Load /WAD_DIRECTORY/wad.json and begin execution." << endl << endl;
  cout << "      --help     display this help and exit" << endl;
}

void CLI::suggestHelp() { cout << "Try 'sprawl --help' for more information." << endl; }

#pragma once

#include "Types.hh"

class CLI {
 public:
  CLI(const int argc, const char* const argv[]);
  bool shouldQuit() const;
  string getWADDir() const;
  string getWADpath() const;
  int getReturnCode() const;

 private:
  bool _quit;
  int _returnCode;
  string _wadDir;

  void suggestHelp();
  void showHelp();
};

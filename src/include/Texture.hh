#pragma once

#include "Types.hh"

class Texture {
  Texture(const FilePathPS path) : path(path){};

 private:
  FilePathPS path;
};

#pragma once

#include "Drawable.hh"
#include "Vect2D.hh"

#define RED_BRICK_TEXTURE_PATH "textures/brick-red.png"
#define ORANGE_BRICK_TEXTURE_PATH "textures/brick-orange.png"
#define YELLOW_BRICK_TEXTURE_PATH "textures/brick-yellow.png"
#define GREEN_BRICK_TEXTURE_PATH "textures/brick-green.png"
#define BLUE_BRICK_TEXTURE_PATH "textures/brick-blue.png"
#define PURPLE_BRICK_TEXTURE_PATH "textures/brick-purple.png"

// Forward decl
class Vect2D;

class Brick : public Drawable {
 public:
  Brick(const Vect2D& center, const int height, const int width, const std::string& texturePath);
};

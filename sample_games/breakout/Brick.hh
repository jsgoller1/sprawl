#pragma once

#include <string_view>
#include <vector>

#include "Drawable.hh"
#include "Vect2D.hh"

#define BRICK_WIDTH 150
#define BRICK_HEIGHT 50

constexpr std::string_view RED_BRICK_TEXTURE_PATH =
    "/Users/joshua/Code/sprawl/sample_games/breakout/textures/brick-red.png";
constexpr std::string_view ORANGE_BRICK_TEXTURE_PATH =
    "/Users/joshua/Code/sprawl/sample_games/breakout/textures/brick-orange.png";
constexpr std::string_view YELLOW_BRICK_TEXTURE_PATH =
    "/Users/joshua/Code/sprawl/sample_games/breakout/textures/brick-yellow.png";
constexpr std::string_view GREEN_BRICK_TEXTURE_PATH =
    "/Users/joshua/Code/sprawl/sample_games/breakout/textures/brick-green.png";
constexpr std::string_view BLUE_BRICK_TEXTURE_PATH =
    "/Users/joshua/Code/sprawl/sample_games/breakout/textures/brick-blue.png";
constexpr std::string_view PURPLE_BRICK_TEXTURE_PATH =
    "/Users/joshua/Code/sprawl/sample_games/breakout/textures/brick-purple.png";

static const std::vector<std::string_view> brickColors = {RED_BRICK_TEXTURE_PATH,    ORANGE_BRICK_TEXTURE_PATH,
                                                          YELLOW_BRICK_TEXTURE_PATH, GREEN_BRICK_TEXTURE_PATH,
                                                          BLUE_BRICK_TEXTURE_PATH,   PURPLE_BRICK_TEXTURE_PATH};

// Forward decl
class Vect2D;

class Brick : public Drawable {
 public:
  Brick(const Vect2D& center, const int width, const int height, const std::string& texturePath);
  ~Brick() override;
  //  SDL_Rect getBoundingBox() const override;

 private:
  // SDL_Rect _boundingBox;
};

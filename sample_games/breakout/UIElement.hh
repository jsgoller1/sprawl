#pragma once

#include "Drawable.hh"

#define VICTORY_TEXTURE_PATH "/Users/joshua/Code/sprawl/sample_games/breakout/textures/victory.png"
#define FAIL_TEXTURE_PATH "/Users/joshua/Code/sprawl/sample_games/breakout/textures/fail.png"
#define BALLS_REMAINING_TEXTURE_PATH "/Users/joshua/Code/sprawl/sample_games/breakout/textures/ui-balls-remaining.png"
#define BALLS_COUNT_3_TEXTURE_PATH "/Users/joshua/Code/sprawl/sample_games/breakout/textures/ui-3.png"
#define BALLS_COUNT_2_TEXTURE_PATH "/Users/joshua/Code/sprawl/sample_games/breakout/textures/ui-2.png"
#define BALLS_COUNT_1_TEXTURE_PATH "/Users/joshua/Code/sprawl/sample_games/breakout/textures/ui-1.png"

class UIElement : public Drawable {
 public:
  UIElement(const Vect2D& center, const int width, const int height, const std::string& texturePath);
  virtual ~UIElement() override;
};

class BallsCounter : public UIElement {
 public:
  BallsCounter(const Vect2D& center, const int width, const int height, const std::string& texturePath,
               const int ballsCount);
  ~BallsCounter() override;
  void decrement();
  int getBallsCount() const;

 private:
  int _ballsCount;
};

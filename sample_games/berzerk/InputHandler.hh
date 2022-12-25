#pragma once
#include "Vect2D.hh"
class InputHandler {
 public:
  bool gotSDLQuit() const;
  bool escapePressed() const;
  bool upArrowPressed() const;
  bool downArrowPressed() const;
  bool leftArrowPressed() const;
  bool rightArrowPressed() const;
  bool lCntrlPressed() const;

  bool bothHorizontalKeysPressed() const;
  bool bothVerticalKeysPressed() const;

  void getKeyboardInput();

 private:
  bool _gotSDLQuit = false;
  bool _escapePressed = false;
  bool _upArrowPressed = false;
  bool _downArrowPressed = false;
  bool _leftArrowPressed = false;
  bool _rightArrowPressed = false;
  bool _lCntrlPressed = false;
};

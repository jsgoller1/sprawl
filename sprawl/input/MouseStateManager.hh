#pragma once

#include "InputStateManager.hh"
#include "Math.hh"

class MouseStateManager : public InputStateManager {
 public:
  MouseStateManager();

  void processEvent(SDL_Event event) override;
  void updateInputs() override;

  InputPressState getMouseButtonState(Uint8 button) const;
  Vect2D getMousePosition() const;
  Vect2D getMousePositionDelta() const;

 private:
  std::map<Uint8, InputPressState> pressedMouseButtons;
  Vect2D mousePosition = Vect2D::zero();
  Vect2D previousMousePosition = Vect2D::zero();
};

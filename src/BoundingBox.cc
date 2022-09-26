#include "BoundingBox.hh"

#include "Math.hh"
#include "Memory.hh"

bool BoundingBox::checkCollision(const shared_ptr<BoundingBox> otherBox) {
  // TODO: SDL implements several functions and types we can use
  // for collision detection; this works fine for now.

  // 0,0 is the upper lefthand corner, see remark:
  // https://wiki.libsdl.org/SDL_SetWindowPosition
  PositionUnit comp1YHighest = this->center->y - (this->height / 2);
  PositionUnit comp1YLowest = this->center->y + (this->height / 2);
  PositionUnit comp1XLeftmost = this->center->x - (this->width / 2);
  PositionUnit comp1XRightmost = this->center->x + (this->width / 2);

  PositionUnit comp2YHighest = otherBox->center->y - (otherBox->height / 2);
  PositionUnit comp2YLowest = otherBox->center->y + (otherBox->height / 2);
  PositionUnit comp2XLeftmost = otherBox->center->x - (otherBox->width / 2);
  PositionUnit comp2XRightmost = otherBox->center->x + (otherBox->width / 2);

  // Highest and Lowest refer to positioning on the screen; numerically,
  // Lowest is greater than Highest
  return areLinesIntersecting(comp1YHighest, comp1YLowest, comp2YHighest,
                              comp2YLowest) &&
         areLinesIntersecting(comp1XLeftmost, comp1XRightmost, comp2XLeftmost,
                              comp2XRightmost);
}

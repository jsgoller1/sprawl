#include "Wall.hh"

#include "SpriteManager.hh"
#include "Vect2D.hh"

// TODO: This is just a temporary hack while we hardcode screen size; we can make the screen adjustable and textures
// stretchable as needed later.
#include "Screen.hh"

static Vect2D getHorizontalWallPosition(const unsigned wallIndex) {
  // The top left corner of the topmost leftmost wall is at (-SCREEN_WIDTH/2, SCREEN_HEIGHT/2), so
  // it's center is offset from that by (wall width / 2, wall height / 2).
  int x = (-INTERNAL_PLAY_AREA_WIDTH / 2) + (HORIZONTAL_WALL_WIDTH / 2);
  // Then for each wall in the sequence, the horizontal offset is multiplied by (wallIndex % 5)
  x += HORIZONTAL_WALL_WIDTH * (wallIndex % 5);

  // For the vertical offset, horizontal walls of each row need to have vertical wall height distance between them
  int y = (INTERNAL_PLAY_AREA_HEIGHT / 2) - (HORIZONTAL_WALL_HEIGHT / 2);
  y -= (VERTICAL_WALL_HEIGHT) * (wallIndex / 5);
  // Correct positioning for wall 0 should be (-550, 395)
  return Vect2D(x, y);
}

static Vect2D getVerticalWallPosition(const unsigned wallIndex) {
  // The top left corner of the topmost leftmost wall is at (-SCREEN_WIDTH/2, SCREEN_HEIGHT/2), so
  // it's center is offset from that by (wall width / 2, wall height / 2).
  int x = (-INTERNAL_PLAY_AREA_WIDTH / 2) + (VERTICAL_WALL_WIDTH / 2);
  // Then for each wall in the sequence, the horizontal offset is multiplied by (wallIndex % 6)
  x += HORIZONTAL_WALL_WIDTH * ((wallIndex % 20) % 6);

  // For the vertical offset, vertical walls of each row need to have vertical wall height distance between them
  int y = (INTERNAL_PLAY_AREA_HEIGHT / 2) - (VERTICAL_WALL_HEIGHT / 2);
  y -= VERTICAL_WALL_HEIGHT * ((wallIndex % 20) / 6);
  return Vect2D(x, y);
}

Vect2D getWallPosition(const unsigned wallIndex) {
  return (wallIndex < 20) ? getHorizontalWallPosition(wallIndex) : getVerticalWallPosition(wallIndex);
}

Wall::Wall(const Vect2D& position, const int height, const int width, const std::shared_ptr<Sprite> sprite,
           DrawingProxy& drawingProxy)
    : GameObject(position, Vect2D::zero()),
      IStaticDrawing(this->getPositionComponent(), height, width, drawingProxy, sprite) {}

Wall::Wall(Wall& copy)
    : Wall(copy.getPosition(), copy.getHeight(), copy.getWidth(), copy.getCurrentSprite(), copy.getDrawingProxy()) {}

void Wall::resolveCollision(GameObject& target) {
  // We actually don't need to do anything when something collides with us; anything colliding with a wall dies
  // painfully (except EvilOtto)
  // TODO: This means then that not every GameObject needs to have collision resolution behavior.
  (void)target;
};

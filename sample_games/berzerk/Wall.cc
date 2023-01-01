#include "Wall.hh"

#include "SpriteManager.hh"
#include "Vect2D.hh"

Wall::Wall(const Vect2D& position, const int height, const int width, const LevelSpriteManager& levelSpriteManager,
           DrawingProxy& drawingProxy)
    : GameObject(position, Vect2D::zero(), height, width, levelSpriteManager, drawingProxy),
      _levelSpriteManager(levelSpriteManager) {}

void Wall::resolveCollision(GameObject& target) {
  // We actually don't need to do anything when something collides with us; anything colliding with a wall dies
  // painfully (except EvilOtto)
  // TODO: This means then that not every GameObject needs to have collision resolution behavior.
  (void)target;
};

const LevelSpriteManager& Wall::getSpriteManager() const { return this->_levelSpriteManager; }

std::shared_ptr<Sprite> Wall::getCurrentSprite() const {
  // TODO: should probably return shared pointers to SDL_Surface all the way around; no issue here with covariant
  // returns.
  return this->getSpriteManager().horizontalBorderWall();
}

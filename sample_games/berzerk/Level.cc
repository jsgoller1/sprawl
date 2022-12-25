#include "Level.hh"

Level::Level(DrawingProxy& drawingProxy, const LevelSpriteManager& levelSpriteManager,
             const PlayerSpriteManager& playerSpriteManager, const RobotSpriteManager& robotSpriteManager,
             const TextSpriteManager& textSpriteManager)
    : _drawingProxy(drawingProxy),
      _levelSpriteManager(levelSpriteManager),
      _playerSpriteManager(playerSpriteManager),
      _robotSpriteManager(robotSpriteManager),
      _textSpriteManager(textSpriteManager) {
  // this->_walls = std::unique_ptr<std::vector<std::shared_ptr<Wall>>>(new std::vector<std::shared_ptr<Wall>>());
}

void Level::updateAnimations() {}
void Level::updateAI() {
  //   Robot* robot;
  //   for (/* each Robot */) {
  //     robot->aiBehavior();
  //   }
}

void Level::moveCharacters() {}

void Level::updateCollisions() {
  // There are not going to be that many walls, robots, or projectiles; probably 10
  // robots and a player, each of whom can fire a projectile (so 22 objects at most). We
  // could try doing 22 x 22 collision tests, but then we have to test walls on top of
  // that. Another option would be a kind of space partitioning; we maintain a
  // list-of-lists of the contents of every room (walls, projectiles, and characters). A
  // character or projectile would test (based on its corners) what room its in before
  // moving and then after, then update the list-of-lists accordingly. We also don't need
  // to test collisions on anything that didn't move.

  //   for (/* source: each bullet, robot, and the player */) {
  //     for (/* target: each wall, bullet, robot, and the player **/) {
  //       if (/* source collides with target */) {
  //         source->resolveCollision(*target);
  //         target->resolveCollision(*source);
  //       }
  //     }
  //   }
}

// std::vector<std::shared_ptr<Wall>>& Level::getWalls() { return *this->_walls; }

void Level::LevelShootingProxy::shoot(const Direction& direction, const Vect2D& origin) const {
  (void)direction;
  (void)origin;

  /*
   * Creates bullet heading in direction with default bullet velocity.
   */
}

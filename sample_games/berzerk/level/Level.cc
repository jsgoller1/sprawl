#include "Level.hh"

#include <iostream>
#include <random>

#include "Bullet.hh"
#include "BulletSpriteManager.hh"
#include "Configs.hh"
#include "Direction.hh"
#include "InputHandler.hh"
#include "LevelSpriteManager.hh"
#include "OttoSpriteManager.hh"
#include "PlayerPositionProxy.hh"
#include "PlayerSpriteManager.hh"

Vect2D getCellCenter(const int cellId) {
  if (cellId < 0 || cellId > 14) {
    return Vect2D::zero();
  }

  Vect2D center = CELL_0_CENTER;
  center.x += (cellId % 5) * HORIZONTAL_WALL_WIDTH;
  center.y -= (cellId / 5) * VERTICAL_WALL_HEIGHT;
  return center;
}

Level::Level(DrawingProxy& drawingProxy, const LevelSpriteManager& levelSpriteManager,
             const PlayerSpriteManager& playerSpriteManager, const RobotSpriteManager& robotSpriteManager,
             const BulletSpriteManager& bulletSpriteManager, const OttoSpriteManager& ottoSpriteManager)
    : _drawingProxy(drawingProxy),
      _levelSpriteManager(levelSpriteManager),
      _playerSpriteManager(playerSpriteManager),
      _robotSpriteManager(robotSpriteManager),
      _ottoSpriteManager(ottoSpriteManager),
      _bulletSpriteManager(bulletSpriteManager),
      _bullets(this->_bulletSpriteManager, drawingProxy),
      _levelShootingProxy(LevelShootingProxy(this->_bullets)),
      _walls(this->generateWalls(), this->_levelSpriteManager, this->_drawingProxy),
      _player(Player(getPlayerSpawnPoint(), Vect2D::zero(), this->_levelShootingProxy, drawingProxy,
                     this->_playerSpriteManager)),
      _playerPositionProxy(PlayerPositionProxy(this->_player)),
      _robots(this->generateRobotStartPositions(ROBOTS_COUNT), this->_levelShootingProxy, this->_drawingProxy,
              this->_playerPositionProxy, this->_robotSpriteManager),
      _otto(Otto(Vect2D(-2000, -2000), this->_drawingProxy, this->_playerPositionProxy, this->_ottoSpriteManager)) {}

void Level::update(const InputHandler& inputHandler, const time_ms deltaT) {
  this->_robots.update(deltaT);
  this->_player.update(inputHandler, deltaT);
  this->_bullets.update(deltaT);
  // this->_otto->update(deltaT);
  this->handleCollisions();
  this->removeMarked();
}

void Level::draw() {
  // The drawing order here matters; we want to draw robots before walls, so their explosion animation is drawn under
  // wall (otherwise it will block out part of the wall; might want to use color keying for this. Player's death
  // animation should be drawn over the wall, so they are drawn last.
  this->_robots.draw();
  this->_player.draw();
  this->_bullets.draw();
  this->_walls.draw();
}

bool Level::playerAtExit() const { return false; }

void Level::handleCollisions() {
  /*
  - Player dies if they collide with robots, bullets, otto, or walls
  - Robots die if they collide with player, robotos, bullets, otto, or walls
  - Bullets disappear if they collide with player, walls, robots, or otto
  - Otto and walls never disappear; Otto can pass through everything

  So we can cover all the above by testing as follows:
  - Player against robots, bullets, otto, and walls
  - Robots against robots, bullets, otto, and walls
  - Bullets against otto and walls

  There are not going to be that many walls, robots, or projectiles; probably 10
  robots and a player, each of whom can fire a projectile (so 22 objects at most). We
  could try doing 22 x 22 collision tests, but then we have to test walls on top of
  that. Another option would be a kind of space partitioning; we maintain a
  list-of-lists of the contents of every room (walls, projectiles, and characters). A
  character or projectile would test (based on its corners) what room its in before
  moving and then after, then update the list-of-lists accordingly. We also don't need
  to test collisions on anything that didn't move.
  */

  // NOTE: Bullet collisions need to be handled before player; otherwise, if a bullet collides with a wall and a player,
  // it will wind up killing the player. Same thing with robot collisions; there's an edge case where a player and robot
  // are standing very close on either side of a wall. If the robot explodes, its sprite will expand but it should not
  // cause the player to die (since there's a wall between them). Testing for robot/wall collisions before robot/player
  // collisions ensures this won't happen.

  this->_robots.collisionTestAndResolve(&this->_player);
  this->_bullets.collisionTestAndResolve(&this->_player);
  this->_walls.collisionTestAndResolve(&this->_player);

  this->_robots.collisionTestAndResolve(&this->_robots);
  this->_bullets.collisionTestAndResolve(&this->_robots);
  this->_walls.collisionTestAndResolve(&this->_robots);

  this->_bullets.collisionTestAndResolve(&this->_walls);
}

void Level::removeMarked() {
  this->_bullets.removeMarked();
  this->_robots.removeMarked();
}

std::vector<Vect2D> Level::generateRobotStartPositions(const int robotsCount) {
  // TODO: Robots need to be generated to they don't spawn on top of player or walls.

  (void)robotsCount;
  std::vector<Vect2D> startPositions = std::vector<Vect2D>{Vect2D{300, 300}};
  return startPositions;
}

std::vector<int> Level::randomizeInternalWalls() {
  std::set<int> chosenWalls = std::set<int>();
  std::set<int> allInternalWallsSet = HORIZONTAL_INTERNAL_WALLS;
  allInternalWallsSet.insert(VERTICAL_INTERNAL_WALLS.begin(), VERTICAL_INTERNAL_WALLS.end());
  std::vector<int> allInternalWalls = std::vector<int>(allInternalWallsSet.begin(), allInternalWallsSet.end());

  // obtain a random number from hardware
  std::random_device rd;
  // seed the generator
  std::mt19937 gen(rd());
  // define the range
  std::uniform_int_distribution<> distr(0, (int)allInternalWalls.size() - 1);

  while (chosenWalls.size() < GENERATED_WALL_COUNT) {
    chosenWalls.insert(allInternalWalls.at((size_t)distr(gen)));
  }
  return std::vector<int>(chosenWalls.begin(), chosenWalls.end());
}

std::vector<int> Level::generateWalls() {
  std::vector<int> walls = this->randomizeInternalWalls();

  for (auto it = HORIZONTAL_BORDER_WALLS.begin(); it != HORIZONTAL_BORDER_WALLS.end(); it++) {
    walls.push_back(*it);
  }
  for (auto it = VERTICAL_BORDER_WALLS.begin(); it != VERTICAL_BORDER_WALLS.end(); it++) {
    walls.push_back(*it);
  }

  return walls;
}

Vect2D Level::getPlayerSpawnPoint() { return Vect2D::zero(); }

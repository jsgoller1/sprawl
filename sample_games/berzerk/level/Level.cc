#include "Level.hh"

#include <iostream>

#include "Bullet.hh"
#include "BulletSpriteManager.hh"
#include "Direction.hh"
#include "InputHandler.hh"
#include "LevelSpriteManager.hh"
#include "OttoSpriteManager.hh"
#include "PlayerPositionProxy.hh"
#include "PlayerSpriteManager.hh"

Level::Level(DrawingProxy& drawingProxy, const LevelSpriteManager& levelSpriteManager,
             const PlayerSpriteManager& playerSpriteManager, const RobotSpriteManager& robotSpriteManager,
             const BulletSpriteManager& bulletSpriteManager, const OttoSpriteManager& ottoSpriteManager)
    : _drawingProxy(drawingProxy),
      _levelSpriteManager(levelSpriteManager),
      _playerSpriteManager(playerSpriteManager),
      _robotSpriteManager(robotSpriteManager),
      _ottoSpriteManager(ottoSpriteManager),
      _bulletSpriteManager(bulletSpriteManager) {
  // TODO: Not sure if I like this constructor; feels shitty to initialize bullets and proxy like above, maybe
  // we want functions like we have below for player, robots, and walls? Although there are no bullets to start
  // with, and each below has initial state we need to set up.
  this->initWalls(this->_levelSpriteManager, this->_drawingProxy);
  this->_bullets = std::unique_ptr<std::vector<std::shared_ptr<Bullet>>>(new std::vector<std::shared_ptr<Bullet>>());
  this->_levelShootingProxy = std::unique_ptr<LevelShootingProxy>(
      new LevelShootingProxy(*this->_bullets, this->_bulletSpriteManager, drawingProxy));
  this->initPlayer(this->_playerSpriteManager, this->_drawingProxy);
  this->_playerPositionProxy = std::unique_ptr<PlayerPositionProxy>(new PlayerPositionProxy(*this->_player));
  this->initRobots(this->_robotSpriteManager, this->_drawingProxy);
  this->initOtto(this->_ottoSpriteManager, this->_drawingProxy);
}

void Level::update(const InputHandler& inputHandler, const time_ms deltaT) {
  this->_player->update(inputHandler, deltaT);
  for (size_t i = 0; i < this->_bullets->size(); i++) {
    (*this->_bullets)[i]->update();
  }
  for (size_t i = 0; i < ROBOTS_COUNT; i++) {
    this->_robots[i]->update(deltaT);
  }
  this->_otto->update(deltaT);
  this->handleCollisions();
  this->removeMarked();
}

void Level::draw() {
  // The drawing order here matters; we want to draw robots before walls, so their explosion animation is drawn under
  // wall (otherwise it will block out part of the wall; might want to use color keying for this. Player's death
  // animation should be drawn over the wall, so they are drawn last.

  for (size_t i = 0; i < this->_bullets->size(); i++) {
    (*this->_bullets)[i]->getDrawingComponent().draw();
  }

  for (int i = 0; i < ROBOTS_COUNT; i++) {
    if (this->_robots[i] != nullptr) {
      this->_robots[i]->getDrawingComponent().draw();
    }
  }

  for (int i = 0; i < WALLS_COUNT; i++) {
    if (this->_walls[i] != nullptr) {
      this->_walls[i]->getDrawingComponent().draw();
    }
  }

  this->_player->getDrawingComponent().draw();
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
  this->handleBulletCollisions();
  this->handleRobotCollisions();
  this->handlePlayerCollisions();
}

void Level::handlePlayerCollisions() {
  if (this->handleCollisionAgainstRobots(this->_player)) {
    return;
  }
  if (this->handleCollisionAgainstBullets(this->_player)) {
    return;
  }
  if (this->handleCollisionAgainstWalls(this->_player)) {
    return;
  }
}

void Level::handleRobotCollisions() {
  for (size_t i = 0; i < ROBOTS_COUNT; i++) {
    if (this->handleCollisionAgainstRobots(this->_robots[i])) {
      continue;
    }
    if (this->handleCollisionAgainstBullets(this->_robots[i])) {
      continue;
    }
    if (this->handleCollisionAgainstWalls(this->_robots[i])) {
      continue;
    }
  }
}

void Level::handleBulletCollisions() {
  for (size_t i = 0; i < this->_bullets->size(); i++) {
    if (this->handleCollisionAgainstWalls(this->_bullets->at(i))) {
      continue;
    }
  }
}

bool Level::handleCollisionAgainstRobots(const std::shared_ptr<GameObject> source) {
  for (size_t i = 0; i < ROBOTS_COUNT; i++) {
    if (this->_robots[i] == source) {
      continue;
    }
    if (source->collisionTest(*this->_robots[i])) {
      source->resolveCollision(*this->_robots[i]);
      this->_robots[i]->resolveCollision(*source);
      return true;
    }
  }
  return false;
}

bool Level::handleCollisionAgainstBullets(const std::shared_ptr<GameObject> source) {
  for (size_t i = 0; i < this->_bullets->size(); i++) {
    if (this->_bullets->at(i) == source) {
      continue;
    }
    if (source->collisionTest(*this->_bullets->at(i))) {
      source->resolveCollision(*this->_bullets->at(i));
      this->_bullets->at(i)->resolveCollision(*source);
      return true;
    }
  }
  return false;
}

bool Level::handleCollisionAgainstWalls(const std::shared_ptr<GameObject> source) {
  std::shared_ptr<Wall> currentWall = nullptr;
  for (size_t i = 0; i < WALLS_COUNT; i++) {
    currentWall = this->_walls[i];
    if (currentWall == nullptr) {
      continue;
    }
    if (source->collisionTest(*currentWall)) {
      source->resolveCollision(*currentWall);
      return true;
    }
  }
  return false;
}

void Level::initWalls(const LevelSpriteManager& levelSpriteManager, DrawingProxy& drawingProxy) {
  //  TODO: Every level should always have border walls; for now though, we want to draw every wall.
  // This function should probably be responsible for the random layout, but not "how to draw walls"
  this->initBorderWalls(levelSpriteManager, drawingProxy);
  this->initInternalWalls(levelSpriteManager, drawingProxy);
}

void Level::initBorderWalls(const LevelSpriteManager& levelSpriteManager, DrawingProxy& drawingProxy) {
  // TODO: The below is a bit janky looking, would prefer not to call the copy constructor for Wall, though I really
  // like having parameters for creating Wall hidden via static methods (i.e. Wall::VerticalBorderWall())

  // Vertical borders
  for (int i = 0; i < VERTICAL_BORDER_WALLS_COUNT; i++) {
    int west = BORDER_WALLS_W[i];
    this->_walls[west] = std::make_shared<Wall>(
        Wall::VerticalBorderWall(getWallPosition((unsigned)west), levelSpriteManager, drawingProxy));
    int east = BORDER_WALLS_E[i];
    this->_walls[east] = std::make_shared<Wall>(
        Wall::VerticalBorderWall(getWallPosition((unsigned)east), levelSpriteManager, drawingProxy));
  }

  // Horizontal borders
  for (int i = 0; i < HORIZONTAL_BORDER_WALLS_COUNT; i++) {
    int north = BORDER_WALLS_N[i];
    this->_walls[north] = std::make_shared<Wall>(
        Wall::HorizontalBorderWall(getWallPosition((unsigned)north), levelSpriteManager, drawingProxy));

    int south = BORDER_WALLS_S[i];
    this->_walls[south] = std::make_shared<Wall>(
        Wall::HorizontalBorderWall(getWallPosition((unsigned)south), levelSpriteManager, drawingProxy));
  }
}

static bool isFixedStateWall(const int idx) {
  for (int i = 0; i < FIXED_LEVEL_LAYOUT_WALLS_COUNT; i++) {
    if (idx == FIXED_LEVEL_LAYOUT_WALLS[i]) {
      return true;
    }
  }
  return false;
}

void Level::initInternalWalls(const LevelSpriteManager& levelSpriteManager, DrawingProxy& drawingProxy) {
  for (int i = 0; i < VERTICAL_INTERNAL_WALLS_COUNT; i++) {
    int idx = VERTICAL_INTERNAL_WALLS[i];
    if (!isFixedStateWall(idx)) {
      continue;
    }
    this->_walls[idx] = std::shared_ptr<Wall>(
        new Wall(Wall::VerticalInternalWall(getWallPosition((unsigned)idx), levelSpriteManager, drawingProxy)));
  }
  for (int i = 0; i < HORIZONTAL_INTERNAL_WALLS_COUNT; i++) {
    int idx = HORIZONTAL_INTERNAL_WALLS[i];
    if (!isFixedStateWall(idx)) {
      continue;
    }
    this->_walls[idx] = std::shared_ptr<Wall>(
        new Wall(Wall::HorizontalInternalWall(getWallPosition((unsigned)idx), levelSpriteManager, drawingProxy)));
  }
}

void Level::initPlayer(const PlayerSpriteManager& playerSpriteManager, DrawingProxy& drawingProxy) {
  // TODO: Randomize player position
  // TODO: Ensure player isn't being drawn on top of robots
  this->_player = std::make_shared<Player>(Vect2D(250, 50), Vect2D::zero(), *this->_levelShootingProxy, drawingProxy,
                                           playerSpriteManager);
}

void Level::initRobots(const RobotSpriteManager& robotSpriteManager, DrawingProxy& drawingProxy) {
  // TODO: to start off with, let's just draw robots
  for (int i = 0; i < ROBOTS_COUNT; i++) {
    this->_robots[0] = std::make_shared<Robot>(Vect2D(250, 250), Vect2D::zero(), *this->_levelShootingProxy,
                                               drawingProxy, *this->_playerPositionProxy, robotSpriteManager);
  }
}

void Level::initOtto(const OttoSpriteManager& ottoSpriteManager, DrawingProxy& drawingProxy) {
  (void)ottoSpriteManager;
  (void)drawingProxy;
}

void Level::removeMarked() {
  for (size_t i = 0; i < this->_bullets->size(); i++) {
    std::shared_ptr<Bullet> bullet = (*this->_bullets)[i];
    if (bullet->getShouldRemove()) {
      (*this->_bullets).erase((*this->_bullets).begin() + (long)i);
    }
  }
}

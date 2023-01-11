#include "Level.hh"

#include <iostream>

#include "InputHandler.hh"
#include "Player.hh"
#include "Wall.hh"

Level::Level(DrawingProxy& drawingProxy, const LevelSpriteManager& levelSpriteManager,
             const PlayerSpriteManager& playerSpriteManager, const RobotSpriteManager& robotSpriteManager)
    : _drawingProxy(drawingProxy),
      _levelSpriteManager(levelSpriteManager),
      _playerSpriteManager(playerSpriteManager),
      _robotSpriteManager(robotSpriteManager) {
  this->_levelShootingProxy = LevelShootingProxy();
  this->initPlayer(this->_playerSpriteManager, this->_drawingProxy);
  this->initRobots(this->_robotSpriteManager, this->_drawingProxy);
  this->initWalls(this->_levelSpriteManager, this->_drawingProxy);
}

void Level::update(const InputHandler& inputHandler, const time_ms deltaT) {
  this->_player->update(inputHandler, deltaT);
  this->updateCollisions();
}

void Level::draw() {
  // TODO: For now, we're just going to draw every game object while knowing what type it is. Later on,
  // maybe we will represent drawable GameObjects with a collection of IDrawables or something?
  this->_player->getDrawingComponent().draw();

  for (int i = 0; i < WALLS_COUNT; i++) {
    if (this->_walls[i] != nullptr) {
      this->_walls[i]->getDrawingComponent().draw();
    }
  }
}

bool Level::playerAtExit() const { return false; }

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
  std::shared_ptr<Wall> currentWall = nullptr;
  for (int i = 0; i < WALLS_COUNT; i++) {
    currentWall = this->_walls[i];
    if (currentWall != nullptr && this->_player->collisionTest(*currentWall)) {
      std::cout << "Player collided with wall " << i << std::endl;
      this->_player->resolveCollision(*currentWall);
    }
  }
}

// std::vector<std::shared_ptr<Wall>>& Level::getWalls() { return *this->_walls; }

void Level::LevelShootingProxy::shoot(const Direction& direction, const Vect2D& origin) const {
  (void)direction;
  (void)origin;

  /*
   * Creates bullet heading in direction with default bullet velocity.
   */
}

void Level::initPlayer(const PlayerSpriteManager& playerSpriteManager, DrawingProxy& drawingProxy) {
  // TODO: Randomize player position
  // TODO: Ensure player isn't being drawn on top of robots
  (void)playerSpriteManager;
  (void)drawingProxy;
  this->_player = std::make_shared<Player>(Vect2D::zero(), Vect2D::zero(), this->_levelShootingProxy, drawingProxy,
                                           playerSpriteManager);
}

void Level::initRobots(const RobotSpriteManager& robotSpriteManager, DrawingProxy& drawingProxy) {
  (void)robotSpriteManager;
  (void)drawingProxy;
}

void Level::initBorderWalls(const LevelSpriteManager& levelSpriteManager, DrawingProxy& drawingProxy) {
  // TODO: The below is super janky looking, though tecnically it works. All we actually want is a shared_ptr<Wall>,
  // and we want to be able to get that from functions that hide some of the parameters to Wall (i.e.
  // Wall::HorizontalBorderWall()). We end up calling one of these functions, passing it to a copy constructor, which is
  // in turn used by new inside shared pointer construction, not at all straightforward. make_shared() has some issue
  // with construct_at, don't know why. Would like to do something less confusing.

  // Vertical borders
  for (int i = 0; i < VERTICAL_BORDER_WALLS_COUNT; i++) {
    int west = BORDER_WALLS_W[i];
    this->_walls[west] = std::shared_ptr<Wall>(
        new Wall(Wall::VerticalBorderWall(getWallPosition((unsigned)west), levelSpriteManager, drawingProxy)));
    int east = BORDER_WALLS_E[i];
    this->_walls[east] = std::shared_ptr<Wall>(
        new Wall(Wall::VerticalBorderWall(getWallPosition((unsigned)east), levelSpriteManager, drawingProxy)));
  }

  // Horizontal borders
  for (int i = 0; i < HORIZONTAL_BORDER_WALLS_COUNT; i++) {
    int north = BORDER_WALLS_N[i];
    this->_walls[north] = std::shared_ptr<Wall>(
        new Wall(Wall::HorizontalBorderWall(getWallPosition((unsigned)north), levelSpriteManager, drawingProxy)));

    int south = BORDER_WALLS_S[i];
    this->_walls[south] = std::shared_ptr<Wall>(
        new Wall(Wall::HorizontalBorderWall(getWallPosition((unsigned)south), levelSpriteManager, drawingProxy)));
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

void Level::initWalls(const LevelSpriteManager& levelSpriteManager, DrawingProxy& drawingProxy) {
  //  TODO: Every level should always have border walls; for now though, we want to draw every wall.
  // This function should probably be responsible for the random layout, but not "how to draw walls"
  this->initBorderWalls(levelSpriteManager, drawingProxy);
  this->initInternalWalls(levelSpriteManager, drawingProxy);
}

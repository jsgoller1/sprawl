#include "Level.hh"

#include <iostream>

#include "Bullet.hh"
#include "BulletSpriteManager.hh"
#include "Direction.hh"
#include "InputHandler.hh"
#include "PlayerSpriteManager.hh"

Level::Level(DrawingProxy& drawingProxy, const LevelSpriteManager& levelSpriteManager,
             const PlayerSpriteManager& playerSpriteManager, const RobotSpriteManager& robotSpriteManager,
             const BulletSpriteManager& bulletSpriteManager)
    : _drawingProxy(drawingProxy),
      _levelSpriteManager(levelSpriteManager),
      _playerSpriteManager(playerSpriteManager),
      _robotSpriteManager(robotSpriteManager),
      _bulletSpriteManager(bulletSpriteManager),
      _bullets(std::unique_ptr<std::vector<std::shared_ptr<Bullet>>>(new std::vector<std::shared_ptr<Bullet>>())),
      _levelShootingProxy(std::unique_ptr<LevelShootingProxy>(
          new LevelShootingProxy(*this->_bullets, this->_bulletSpriteManager, drawingProxy))) {
  // TODO: Not sure if I like this constructor; feels shitty to initialize bullets and proxy like above, maybe
  // we want functions like we have below for player, robots, and walls? Although there are no bullets to start
  // with, and each below has initial state we need to set up.
  this->initPlayer(this->_playerSpriteManager, this->_drawingProxy);
  this->initRobots(this->_robotSpriteManager, this->_drawingProxy);
  this->initWalls(this->_levelSpriteManager, this->_drawingProxy);
}

void Level::update(const InputHandler& inputHandler, const time_ms deltaT) {
  this->_player->update(inputHandler, deltaT);
  for (size_t i = 0; i < this->_bullets->size(); i++) {
    (*this->_bullets)[i]->update();
  }
  this->updateCollisions();
  this->removeMarked();
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

  for (size_t i = 0; i < this->_bullets->size(); i++) {
    (*this->_bullets)[i]->getDrawingComponent().draw();
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
    if (currentWall == nullptr) {
      continue;
    }
    if (this->_player->collisionTest(*currentWall)) {
      std::cout << "Player collided with wall " << i << std::endl;
      this->_player->resolveCollision(*currentWall);
    }
    for (size_t i = 0; i < this->_bullets->size(); i++) {
      if ((*this->_bullets)[i]->collisionTest(*currentWall)) {
        (*this->_bullets)[i]->resolveCollision(*currentWall);
      }
    }
  }
}

void Level::initPlayer(const PlayerSpriteManager& playerSpriteManager, DrawingProxy& drawingProxy) {
  // TODO: Randomize player position
  // TODO: Ensure player isn't being drawn on top of robots
  (void)playerSpriteManager;
  (void)drawingProxy;
  this->_player = std::make_shared<Player>(Vect2D::zero(), Vect2D::zero(), *this->_levelShootingProxy, drawingProxy,
                                           playerSpriteManager);
}

void Level::initRobots(const RobotSpriteManager& robotSpriteManager, DrawingProxy& drawingProxy) {
  // TODO: to start off with, let's just draw robots

  (void)robotSpriteManager;
  (void)drawingProxy;
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

void Level::initWalls(const LevelSpriteManager& levelSpriteManager, DrawingProxy& drawingProxy) {
  //  TODO: Every level should always have border walls; for now though, we want to draw every wall.
  // This function should probably be responsible for the random layout, but not "how to draw walls"
  this->initBorderWalls(levelSpriteManager, drawingProxy);
  this->initInternalWalls(levelSpriteManager, drawingProxy);
}

void Level::removeMarked() {
  if (this->_player->getShouldRemove()) {
    this->_player = nullptr;
  }
  for (size_t i = 0; i < this->_bullets->size(); i++) {
    std::shared_ptr<Bullet> bullet = (*this->_bullets)[i];
    if (bullet->getShouldRemove()) {
      (*this->_bullets).erase((*this->_bullets).begin() + (long)i);
    }
  }
}

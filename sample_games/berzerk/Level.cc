#include "Level.hh"

#include "InputHandler.hh"

// TODO: This is just a temporary hack while we hardcode screen size; we can make the screen adjustable and textures
// stretchable as needed later.
#include "Screen.hh"

Vect2D getWallPosition(const unsigned wallIndex) {
  if (wallIndex < 19) {
    // Horizontal wall; the top left corner of the topmost leftmost wall is at (-SCREEN_WIDTH, SCREEN_HEIGHT), so it's
    // center is at (wall width / 2, wall height / 2)
    // int row = wallIndex / 5;
    // int col = wallIndex % 5;
    return Vect2D::zero();
  } else {
    // Vertical wall
    return Vect2D::zero();
  }
}

Level::Level(DrawingProxy& drawingProxy, const LevelSpriteManager& levelSpriteManager,
             const PlayerSpriteManager& playerSpriteManager, const RobotSpriteManager& robotSpriteManager)
    : _drawingProxy(drawingProxy),
      _levelSpriteManager(levelSpriteManager),
      _playerSpriteManager(playerSpriteManager),
      _robotSpriteManager(robotSpriteManager) {
  this->initPlayer(this->_playerSpriteManager, this->_drawingProxy);
  this->initRobots(this->_robotSpriteManager, this->_drawingProxy);
  this->initWalls(this->_levelSpriteManager, this->_drawingProxy);
}

void Level::update(const InputHandler& inputHandler) {
  this->updatePlayer(inputHandler);
  this->updateAI();
  this->updateAnimations();
  this->moveCharacters();
  this->updateCollisions();
}

void Level::draw() {
  // TODO: For now, we're just going to draw every game object while knowing what type it is. Later on,
  // maybe we will represent drawable GameObjects with a collection of IDrawables or something?
  for (int i = 0; i < WALLS_COUNT; i++) {
    if (this->_walls[i] != nullptr) {
      this->_walls[i]->draw();
    }
  }
}

bool Level::playerAtExit() const { return false; }

/* Private */
void Level::updatePlayer(const InputHandler& inputHandler) {
  // TODO: Handle player movement and shooting here.
  (void)inputHandler;
}

void Level::updateAI() {
  //   Robot* robot;
  //   for (/* each Robot */) {
  //     robot->aiBehavior();
  //   }
}

void Level::updateAnimations() {}

void Level::moveCharacters() {
  /*
  for each bullet, robot, and the character:
    Move in the direction of its velocity
  */
}

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

void Level::initPlayer(const PlayerSpriteManager& playerSpriteManager, DrawingProxy& drawingProxy) {
  (void)playerSpriteManager;
  (void)drawingProxy;
}

void Level::initRobots(const RobotSpriteManager& robotSpriteManager, DrawingProxy& drawingProxy) {
  (void)robotSpriteManager;
  (void)drawingProxy;
}

void Level::initWalls(const LevelSpriteManager& levelSpriteManager, DrawingProxy& drawingProxy) {
  /*
  //  Every level should always have border walls.
  for (int i = 0; i < 4; i++) {
    int north = BORDER_WALLS_N[i], south = BORDER_WALLS_S[i];
    this->_walls[north] = std::unique_ptr<Wall>(new Wall());
    this->_walls[south] = std::unique_ptr<Wall>(new Wall());
  }
  */
  this->_walls[0] = std::unique_ptr<Wall>(
      new Wall(Vect2D::zero(), VERTICAL_WALL_HEIGHT, VERTICAL_WALL_WIDTH, levelSpriteManager, drawingProxy));
}

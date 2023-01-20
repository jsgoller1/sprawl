#pragma once
#include <memory>
#include <string>
#include <vector>

#include "LevelShootingProxy.hh"
#include "Otto.hh"
#include "Player.hh"
#include "Robot.hh"
#include "Time.hh"
#include "Vect2D.hh"
#include "Wall.hh"

// Fwd decls
class Bullet;
class BulletSpriteManager;
class Direction;
class DrawingProxy;
class InputHandler;
class LevelSpriteManager;
class OttoSpriteManager;
class PlayerSpriteManager;
class PlayerPositionProxy;
class RobotSpriteManager;

/*
 * Berserk levels are always the same size
 * and are always constructed the same way,
 * so we can safely label each wall and then
 * use constants to grab specific ones.
 *
 *   ——0—— ——1—— ——2—— ——3—— ——4——
 *  |     |     |     |     |     |
 *  20    21    22    23    24    25
 *  |     |     |     |     |     |
 *   ——5—— ——6—— ——7—— ——8—— ——9——
 *  |     |     |     |     |     |
 *  26    27    28    29    30    31
 *  |     |     |     |     |     |
 *   ——10— ——11— ——12— ——13— ——14—
 *  |     |     |     |     |     |
 *  32    33    34    35    36    37
 *  |     |     |     |     |     |
 *   ——15— ——16— ——17— ——18— ——19—
 */

constexpr int WALLS_COUNT = 38;
constexpr int HORIZONTAL_BORDER_WALLS_COUNT = 4;
constexpr int BORDER_WALLS_N[] = {0, 1, 3, 4};
constexpr int BORDER_WALLS_S[] = {15, 16, 18, 19};
constexpr int VERTICAL_BORDER_WALLS_COUNT = 2;
constexpr int BORDER_WALLS_W[] = {20, 32};
constexpr int BORDER_WALLS_E[] = {25, 37};
constexpr int EXIT_N = 2;
constexpr int EXIT_S = 17;
constexpr int EXIT_W = 26;
constexpr int EXIT_E = 31;
constexpr int EXIT_COUNT = 4;
constexpr int HORIZONTAL_INTERNAL_WALLS_COUNT = 10;
constexpr int HORIZONTAL_INTERNAL_WALLS[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
constexpr int VERTICAL_INTERNAL_WALLS_COUNT = 12;
constexpr int VERTICAL_INTERNAL_WALLS[] = {21, 22, 23, 24, 27, 28, 29, 30, 33, 34, 35, 36};
constexpr int FIXED_LEVEL_LAYOUT_WALLS_COUNT = 6;
constexpr int FIXED_LEVEL_LAYOUT_WALLS[] = {21, 27, 8, 9, 35, 34};
constexpr int ROBOTS_COUNT = 1;
const Vect2D NORTH_START_POSITION =
    Vect2D(getWallPosition(EXIT_N).x, getWallPosition(EXIT_N).y - VERTICAL_WALL_HEIGHT / 2);

class Level {
 public:
  Level(DrawingProxy& drawingProxy, const LevelSpriteManager& levelSpriteManager,
        const PlayerSpriteManager& playerSpriteManager, const RobotSpriteManager& robotSpriteManager,
        const BulletSpriteManager& bulletSpriteManager, const OttoSpriteManager& ottoSpriteManager);

  bool playerAtExit() const;
  void update(const InputHandler& inputHandler, const time_ms delta_t);
  void draw();

 private:
  DrawingProxy& _drawingProxy;
  std::unique_ptr<LevelShootingProxy> _levelShootingProxy;

  const LevelSpriteManager& _levelSpriteManager;
  std::shared_ptr<Wall> _walls[WALLS_COUNT];

  const PlayerSpriteManager& _playerSpriteManager;
  std::shared_ptr<Player> _player;
  std::unique_ptr<PlayerPositionProxy> _playerPositionProxy;

  // TODO: for now, let's just support a fixed number of robots per level
  const RobotSpriteManager& _robotSpriteManager;
  std::shared_ptr<Robot> _robots[ROBOTS_COUNT];

  const OttoSpriteManager& _ottoSpriteManager;
  std::shared_ptr<Otto> _otto;

  const BulletSpriteManager& _bulletSpriteManager;
  std::unique_ptr<std::vector<std::shared_ptr<Bullet>>> _bullets;

  void initWalls(const LevelSpriteManager& levelSpriteManager, DrawingProxy& drawingProxy);
  void initInternalWalls(const LevelSpriteManager& levelSpriteManager, DrawingProxy& drawingProxy);
  void initBorderWalls(const LevelSpriteManager& levelSpriteManager, DrawingProxy& drawingProxy);
  void initPlayer(const PlayerSpriteManager& playerSpriteManager, DrawingProxy& drawingProxy);
  void initRobots(const RobotSpriteManager& robotSpriteManager, DrawingProxy& drawingProxy);
  void initOtto(const OttoSpriteManager& ottoSpriteManager, DrawingProxy& drawingProxy);
  void removeMarked();

  // Game loop functions
  void handleCollisions();
  // These are named by the collision source (e.g. handlePlayerCollisions() tests
  // if the player collides with anything
  void handlePlayerCollisions();
  void handleRobotCollisions();
  void handleBulletCollisions();

  // These are named by the collision target (e.g. testCollisionWithRobots() tests
  // if something collides with any robots
  bool handleCollisionAgainstRobots(const std::shared_ptr<GameObject> source);
  bool handleCollisionAgainstBullets(const std::shared_ptr<GameObject> source);
  bool handleCollisionAgainstWalls(const std::shared_ptr<GameObject> source);
};

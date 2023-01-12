#pragma once
#include <memory>
#include <string>
#include <vector>

#include "LevelShootingProxy.hh"
#include "Player.hh"
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
class PlayerSpriteManager;
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
const Vect2D NORTH_START_POSITION =
    Vect2D(getWallPosition(EXIT_N).x, getWallPosition(EXIT_N).y - VERTICAL_WALL_HEIGHT / 2);

class Level {
 public:
  Level(DrawingProxy& drawingProxy, const LevelSpriteManager& levelSpriteManager,
        const PlayerSpriteManager& playerSpriteManager, const RobotSpriteManager& robotSpriteManager,
        const BulletSpriteManager& bulletSpriteManager);

  bool playerAtExit() const;
  void update(const InputHandler& inputHandler, const time_ms delta_t);
  void draw();

 private:
  // Owns walls, player, bullets from player, robots, and bullets from robots collection<Wall*> _walls;

  DrawingProxy& _drawingProxy;
  const LevelSpriteManager& _levelSpriteManager;
  const PlayerSpriteManager& _playerSpriteManager;
  const RobotSpriteManager& _robotSpriteManager;
  const BulletSpriteManager& _bulletSpriteManager;
  std::shared_ptr<Player> _player;
  std::unique_ptr<std::vector<std::shared_ptr<Bullet>>> _bullets;
  std::shared_ptr<Wall> _walls[38];
  std::unique_ptr<LevelShootingProxy> _levelShootingProxy;

  void initPlayer(const PlayerSpriteManager& playerSpriteManager, DrawingProxy& drawingProxy);
  void initRobots(const RobotSpriteManager& robotSpriteManager, DrawingProxy& drawingProxy);
  void initInternalWalls(const LevelSpriteManager& levelSpriteManager, DrawingProxy& drawingProxy);
  void initBorderWalls(const LevelSpriteManager& levelSpriteManager, DrawingProxy& drawingProxy);
  void initWalls(const LevelSpriteManager& levelSpriteManager, DrawingProxy& drawingProxy);

  // Game loop functions
  void removeMarked();
  void updateCollisions();
};

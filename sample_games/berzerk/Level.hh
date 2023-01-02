#pragma once
#include <memory>
#include <string>
#include <vector>

#include "ShootingProxy.hh"
#include "SpriteManager.hh"
#include "Wall.hh"

// Fwd decls
class Direction;
class DrawingProxy;
class InputHandler;
class Vect2D;

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

constexpr int WALLS_COUNT = 37;
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
constexpr int INTERNAL_WALLS[] = {5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18,
                                  19, 21, 22, 23, 24, 27, 28, 29, 30, 33, 34, 35, 36};
constexpr int INTERNAL_WALLS_COUNT =
    WALLS_COUNT - VERTICAL_BORDER_WALLS_COUNT - HORIZONTAL_BORDER_WALLS_COUNT - EXIT_COUNT;

class Level {
 public:
  Level(DrawingProxy& drawingProxy, const LevelSpriteManager& levelSpriteManager,
        const PlayerSpriteManager& playerSpriteManager, const RobotSpriteManager& robotSpriteManager);

  bool playerAtExit() const;
  void update(const InputHandler& inputHandler);
  void draw();

 private:
  // Owns walls, player, bullets from player, robots, and bullets from robots collection<Wall*> _walls;
  class LevelShootingProxy : public ShootingProxy {
   public:
    void shoot(const Direction& direction, const Vect2D& origin) const override;
  };

  DrawingProxy& _drawingProxy;
  const LevelSpriteManager& _levelSpriteManager;
  const PlayerSpriteManager& _playerSpriteManager;
  const RobotSpriteManager& _robotSpriteManager;
  std::shared_ptr<Wall> _walls[38];

  void initPlayer(const PlayerSpriteManager& playerSpriteManager, DrawingProxy& drawingProxy);
  void initRobots(const RobotSpriteManager& robotSpriteManager, DrawingProxy& drawingProxy);
  void initWalls(const LevelSpriteManager& levelSpriteManager, DrawingProxy& drawingProxy);

  // Core game loop functions
  void updatePlayer(const InputHandler& inputHandler);
  void updateAI();
  void updateAnimations();
  void moveCharacters();
  void updateCollisions();
};

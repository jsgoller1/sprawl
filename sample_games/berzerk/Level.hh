#pragma once
#include <memory>
#include <string>
#include <vector>

#include "ShootingProxy.hh"
#include "SpriteManager.hh"

// Fwd decls
class Wall;
class Direction;
class Vect2D;
class DrawingProxy;

class Level {
 public:
  /*
   * Berserk levels are always the same size
   * and are always constructed the same way,
   * so we can safely label each wall and then
   * use getters to grab specific ones.
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

  Level(DrawingProxy& drawingProxy, const LevelSpriteManager& levelSpriteManager,
        const PlayerSpriteManager& playerSpriteManager, const RobotSpriteManager& robotSpriteManager,
        const TextSpriteManager& textSpriteManager);

  // Core game loop functions
  void updateAnimations();
  void updateAI();
  void updateCollisions();
  void moveCharacters();

  bool playerAtExit() const;

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
  const TextSpriteManager& _textSpriteManager;
  std::unique_ptr<std::vector<std::shared_ptr<Wall>>> _horizontalWalls;
  std::unique_ptr<std::vector<std::shared_ptr<Wall>>> _verticalWalls;
};

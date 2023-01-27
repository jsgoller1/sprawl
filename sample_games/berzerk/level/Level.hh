#pragma once
#include <memory>
#include <string>
#include <vector>

#include "BulletCollection.hh"
#include "Configs.hh"
#include "LevelShootingProxy.hh"
#include "Otto.hh"
#include "Player.hh"
#include "Robot.hh"
#include "RobotCollection.hh"
#include "Time.hh"
#include "Vect2D.hh"
#include "Wall.hh"
#include "WallCollection.hh"

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
 * Berserk levels are always the same size and are always constructed the same way,
 * so we can safely label each wall and then use constants to grab specific ones.
 * We can also index each cell in a similar fashion (shown by numbers in the center of each cell)
 *
 *   ————0———— ————1———— ————2———— ————3————  ————4————
 *  |         |         |         |          |         |
 *  20   0    21   1    22   2    23   3     24   4    25
 *  |         |         |         |          |         |
 *   ————5———— ————6———— ————7———— ————8————— ————9————
 *  |         |         |         |          |         |
 *  26   5    27   6    28   7    29   8     30   9    31
 *  |         |         |         |          |         |
 *   ————10——— ————11——— ————12——— ————13———— ————14————
 *  |         |         |         |          |         |
 *  32   10   33   11   34   12   35   13    36   14   37
 *  |         |         |         |          |         |
 *   ————15——— ————16——— ————17——— ————18———— ————19————
 */

Vect2D getCellCenter(const int cellId);

class Level {
 public:
  Level(DrawingProxy& drawingProxy, const LevelSpriteManager& levelSpriteManager,
        const PlayerSpriteManager& playerSpriteManager, const RobotSpriteManager& robotSpriteManager,
        const BulletSpriteManager& bulletSpriteManager, const OttoSpriteManager& ottoSpriteManager);

  void update(const InputHandler& inputHandler, const time_ms delta_t);
  void draw();

 private:
  DrawingProxy& _drawingProxy;

  // TODO: We probably don't need to store references here
  const LevelSpriteManager& _levelSpriteManager;
  const PlayerSpriteManager& _playerSpriteManager;
  const RobotSpriteManager& _robotSpriteManager;
  const OttoSpriteManager& _ottoSpriteManager;
  const BulletSpriteManager& _bulletSpriteManager;

  BulletCollection _bullets;
  LevelShootingProxy _levelShootingProxy;
  WallCollection _walls;
  Player _player;
  PlayerPositionProxy _playerPositionProxy;
  RobotCollection _robots;
  Otto _otto;

  bool playerAtExit() const;
  void handleCollisions();
  void removeMarked();
  std::vector<Vect2D> generateRobotStartPositions(const int robotsCount);
  std::vector<int> generateInternalWalls();
  Vect2D getPlayerSpawnPoint();
};

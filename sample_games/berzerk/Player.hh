#pragma once

#include <map>

#include "GameObject.hh"
#include "IAnimatedDrawing.hh"
#include "IShooting.hh"

// Forward decls
class PlayerSpriteManager;
class AnimationSequence;

enum PlayerState {
  // NOTE: the original arcade used west/east facing animations for moving north and south;
  // there was no "moving north" animation.
  IDLE,
  MOVING_W,
  MOVING_E,
  SHOOTING_N,
  SHOOTING_E,
  SHOOTING_S,
  SHOOTING_W,
  SHOOTING_NE,
  SHOOTING_SE,
  SHOOTING_NW,
  SHOOTING_SW,
  DYING
};

class PlayerAnimationSet {
 public:
  PlayerAnimationSet(const PlayerSpriteManager& playerSpriteManager);
  std::shared_ptr<AnimationSequence> getAnimation(const PlayerState& state);

 private:
  std::map<PlayerState, std::shared_ptr<AnimationSequence>> _animations;
};

/*
 *  Player needs to satisfy the following constructors:
 *
 *  GameObject(const Vect2D& position, const Vect2D& velocity);
 *  IShooting(ShootingProxy& shootingProxy);
 *  IAnimatedDrawing(PositionComponent& _positionComponent, const int height, const int width, DrawingProxy&
 *    drawingProxy, const std::shared_ptr<AnimationSequence> animation);
 *
 */
class Player : public GameObject, public IShooting, public IAnimatedDrawing {
 public:
  Player(const Vect2D& position, const Vect2D& velocity, ShootingProxy& shootingProxy, DrawingProxy& drawingProxy,
         const PlayerSpriteManager& playerSpriteManager);
  void resolveCollision(GameObject& target) override;

 private:
  std::unique_ptr<PlayerAnimationSet> _playerAnimationSet;
};

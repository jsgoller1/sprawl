#pragma once

#include <map>

#include "GameObject.hh"
#include "IAnimatedDrawing.hh"
#include "IShooting.hh"
#include "PlayerAnimationSet.hh"
#include "PlayerState.hh"

constexpr int PLAYER_MOVE_SPEED = 5;

// Forward decls
class AnimationSequence;
class InputHandler;
class PlayerSpriteManager;

Vect2D getBulletPositionOffset(const Vect2D& shooterPosition);

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
  void update(const InputHandler& inputHandler, const time_ms deltaT);

 private:
  PlayerState _state;
  std::unique_ptr<PlayerAnimationSet> _playerAnimationSet = nullptr;

  PlayerState updateState(const PlayerState currentState, const InputHandler& inputHandler) const;
  Vect2D updateVelocity(const PlayerState currentState, const InputHandler& inputHandler) const;
  void updateAnimation(const time_ms deltaT, const Direction& movementDirection, const PlayerState oldState,
                       const PlayerState newState);
};

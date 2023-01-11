#pragma once

#include <map>

#include "AnimatedDrawingComponent.hh"
#include "GameObject.hh"
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
 *  AnimatedDrawingComponent(PositionComponent& _positionComponent, const int height, const int width, DrawingProxy&
 *    drawingProxy, const std::shared_ptr<AnimationSequence> animation);
 *
 */
class Player : public GameObject, public IShooting {
 public:
  Player(const Vect2D& position, const Vect2D& velocity, ShootingProxy& shootingProxy, DrawingProxy& drawingProxy,
         const PlayerSpriteManager& playerSpriteManager);

  AnimatedDrawingComponent& getDrawingComponent() const override;

  void resolveCollision(GameObject& target) override;
  void update(const InputHandler& inputHandler, const time_ms deltaT);

 private:
  PlayerState _state;
  std::unique_ptr<AnimatedDrawingComponent> _drawingComponent;
  std::unique_ptr<PlayerAnimationSet> _playerAnimationSet = nullptr;

  PlayerState getNewState(const PlayerState currentState, const InputHandler& inputHandler) const;
  Vect2D getNewVelocity(const PlayerState currentState, const InputHandler& inputHandler) const;
  void updateAnimation(const time_ms deltaT, const Direction& movementDirection, const PlayerState state);
};

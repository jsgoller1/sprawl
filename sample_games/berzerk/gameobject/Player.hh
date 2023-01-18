#pragma once

#include <map>

#include "AnimatedDrawingComponent.hh"
#include "GameObject.hh"
#include "IShooting.hh"
#include "PlayerAnimationSet.hh"
#include "State.hh"

constexpr int PLAYER_MOVE_SPEED = 5;

// Forward decls
class AnimationSequence;
class InputHandler;
class PlayerSpriteManager;

Vect2D getBulletPositionOffset(const Vect2D& shooterPosition);

class Player : public GameObject, public IShooting {
 public:
  Player(const Vect2D& position, const Vect2D& velocity, LevelShootingProxy& shootingProxy, DrawingProxy& drawingProxy,
         const PlayerSpriteManager& playerSpriteManager);

  AnimatedDrawingComponent& getDrawingComponent() const override;

  void resolveCollision(GameObject& target) override;
  void update(const InputHandler& inputHandler, const time_ms deltaT);

 private:
  CharacterState _state;
  time_ms _sinceLastShot;
  std::unique_ptr<PlayerAnimationSet> _playerAnimationSet = nullptr;
  std::unique_ptr<AnimatedDrawingComponent> _drawingComponent = nullptr;

  CharacterState getNewState(const CharacterState currentState, const InputHandler& inputHandler) const;
  Vect2D getNewVelocity(const CharacterState currentState, const InputHandler& inputHandler) const;
  void updateAnimation(const time_ms deltaT, const Direction& movementDirection, const CharacterState state);
};

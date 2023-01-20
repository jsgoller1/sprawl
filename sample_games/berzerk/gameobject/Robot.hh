#pragma once

#include "AnimatedDrawingComponent.hh"
#include "GameObject.hh"
#include "IShooting.hh"
#include "PlayerPositionProxy.hh"
#include "RobotAnimationSet.hh"
#include "State.hh"
#include "Time.hh"

// Fwd decls
class Direction;
class DrawingProxy;
class InputHandler;
class LevelShootingProxy;
class RobotSpriteManager;

class Robot : public GameObject, public IShooting {
 public:
  Robot(const Vect2D& position, const Vect2D& velocity, LevelShootingProxy& shootingProxy, DrawingProxy& drawingProxy,
        const PlayerPositionProxy& playerPositionProxy, const RobotSpriteManager& robotSpriteManager);

  AnimatedDrawingComponent& getDrawingComponent() const override;

  void resolveCollision(GameObject& target) override;
  void update(const time_ms deltaT);

 private:
  const PlayerPositionProxy& _playerPositionProxy;
  CharacterState _state = CharacterState::IDLE;
  time_ms _sinceLastShot = 0;
  std::unique_ptr<AnimatedDrawingComponent> _drawingComponent;
  std::unique_ptr<RobotAnimationSet> _robotAnimationSet = nullptr;

  CharacterState getNewState(const CharacterState currentState) const;
  Vect2D getNewVelocity(const CharacterState currentState) const;
  void updateAnimation(const time_ms deltaT, const Direction& movementDirection, const CharacterState state);
  void shootingBehavior(const time_ms deltaT);

  bool withinRangeOfPlayer() const;
  Direction getShootingDirection() const;
};

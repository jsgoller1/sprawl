#pragma once

#include "AnimatedDrawingComponent.hh"
#include "GameObject.hh"
#include "IShooting.hh"
#include "RobotAnimationSet.hh"
#include "State.hh"

// TODO: Robot should move, shoot, and animate
// faster as fewer remain
constexpr int ROBOT_MOVE_SPEED = 5;

// Fwd decls
class LevelShootingProxy;
class DrawingProxy;
class InputHandler;
class RobotSpriteManager;

class Robot : public GameObject, public IShooting {
 public:
  Robot(const Vect2D& position, const Vect2D& velocity, LevelShootingProxy& shootingProxy, DrawingProxy& drawingProxy,
        const RobotSpriteManager& robotSpriteManager);

  AnimatedDrawingComponent& getDrawingComponent() const override;

  void resolveCollision(GameObject& target) override;
  void update(const time_ms deltaT);

 private:
  CharacterState _state = CharacterState::IDLE;
  // time_ms _sinceLastShot = 0;
  std::unique_ptr<AnimatedDrawingComponent> _drawingComponent;
  std::unique_ptr<RobotAnimationSet> _robotAnimationSet = nullptr;

  Direction lineScan(const GameObject& target);
  void aiBehavior(const Vect2D& playerPosition);
};

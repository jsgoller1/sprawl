#pragma once

#include <map>
#include <memory>

#include "AnimationSequence.hh"

// Fwd decls
class PlayerSpriteManager;

class PlayerAnimationSet {
 public:
  PlayerAnimationSet(const PlayerSpriteManager& playerSpriteManager);

  std::shared_ptr<AnimationSequence> getMovingWSequence() const;
  std::shared_ptr<AnimationSequence> getMovingESequence() const;
  std::shared_ptr<AnimationSequence> getDyingSequence() const;

  std::shared_ptr<AnimationSequence> getShootingNSequence() const;
  std::shared_ptr<AnimationSequence> getShootingESequence() const;
  std::shared_ptr<AnimationSequence> getShootingSSequence() const;
  std::shared_ptr<AnimationSequence> getShootingWSequence() const;
  std::shared_ptr<AnimationSequence> getShootingNESequence() const;
  std::shared_ptr<AnimationSequence> getShootingSESequence() const;
  std::shared_ptr<AnimationSequence> getShootingNWSequence() const;
  std::shared_ptr<AnimationSequence> getShootingSWSequence() const;
  std::shared_ptr<AnimationSequence> getIdleSequence() const;

 private:
  std::shared_ptr<AnimationSequence> _movingWSequence;
  std::shared_ptr<AnimationSequence> _movingESequence;
  std::shared_ptr<AnimationSequence> _dyingSequence;

  std::shared_ptr<AnimationSequence> _shootingNSequence;
  std::shared_ptr<AnimationSequence> _shootingESequence;
  std::shared_ptr<AnimationSequence> _shootingSSequence;
  std::shared_ptr<AnimationSequence> _shootingWSequence;
  std::shared_ptr<AnimationSequence> _shootingNESequence;
  std::shared_ptr<AnimationSequence> _shootingSESequence;
  std::shared_ptr<AnimationSequence> _shootingNWSequence;
  std::shared_ptr<AnimationSequence> _shootingSWSequence;
  std::shared_ptr<AnimationSequence> _idleSequence;
};

#include "PlayerAnimationSet.hh"

#include <iostream>
#include <vector>

#include "Direction.hh"
#include "PlayerSpriteManager.hh"
#include "PlayerState.hh"
#include "Sprite.hh"

// fwd decls
class PlayerSpriteManager;

// NOTE: These class definitions can be private; the fact they are specialized versions of AnimationSequence
// is an implementation detail no one outside this module needs to know.
class MovingWSequence : public AnimationSequence {
 public:
  MovingWSequence(const PlayerSpriteManager& playerSpriteManager) : AnimationSequence() {
    for (int i = 0; i < 3; i++) {
      this->addSprite(playerSpriteManager.movingW(i));
    }
  }
};

class MovingESequence : public AnimationSequence {
 public:
  MovingESequence(const PlayerSpriteManager& playerSpriteManager) : AnimationSequence() {
    for (int i = 0; i < 3; i++) {
      this->addSprite(playerSpriteManager.movingE(i));
    }
  }
};

class DyingSequence : public AnimationSequence {
 public:
  DyingSequence(const PlayerSpriteManager& playerSpriteManager) : AnimationSequence() {
    for (int i = 0; i < 8; i++) {
      this->addSprite(playerSpriteManager.dying(i));
    }
  }
};

// TODO: This class is probably unnecessary; we could just have PlayerSpriteManager return
// AnimationSequences, although then it becomes less reusable since it's tied directly
// to animation. Gonna leave this here for now.
PlayerAnimationSet::PlayerAnimationSet(const PlayerSpriteManager& playerSpriteManager) {
  this->_movingWSequence = std::make_shared<MovingWSequence>(playerSpriteManager);
  this->_movingESequence = std::make_shared<MovingESequence>(playerSpriteManager);
  this->_dyingSequence = std::make_shared<DyingSequence>(playerSpriteManager);

  std::cout << "Loading shooting sequence: N" << std::endl;
  this->_shootingNSequence = std::make_shared<AnimationSequence>(playerSpriteManager.shootingN());
  std::cout << "Loading shooting sequence: E" << std::endl;
  this->_shootingESequence = std::make_shared<AnimationSequence>(playerSpriteManager.shootingE());
  std::cout << "Loading shooting sequence: S" << std::endl;
  this->_shootingSSequence = std::make_shared<AnimationSequence>(playerSpriteManager.shootingS());
  std::cout << "Loading shooting sequence: W" << std::endl;
  this->_shootingWSequence = std::make_shared<AnimationSequence>(playerSpriteManager.shootingW());
  std::cout << "Loading shooting sequence: NE" << std::endl;
  this->_shootingNESequence = std::make_shared<AnimationSequence>(playerSpriteManager.shootingNE());
  std::cout << "Loading shooting sequence: SE" << std::endl;
  this->_shootingSESequence = std::make_shared<AnimationSequence>(playerSpriteManager.shootingSE());
  std::cout << "Loading shooting sequence: NW" << std::endl;
  this->_shootingNWSequence = std::make_shared<AnimationSequence>(playerSpriteManager.shootingNW());
  std::cout << "Loading shooting sequence: SW" << std::endl;
  this->_shootingSWSequence = std::make_shared<AnimationSequence>(playerSpriteManager.shootingSW());
  this->_idleSequence = std::make_shared<AnimationSequence>(playerSpriteManager.standing());
};

std::shared_ptr<AnimationSequence> PlayerAnimationSet::getMovingWSequence() const { return this->_movingWSequence; }
std::shared_ptr<AnimationSequence> PlayerAnimationSet::getMovingESequence() const { return this->_movingESequence; }
std::shared_ptr<AnimationSequence> PlayerAnimationSet::getDyingSequence() const { return this->_dyingSequence; }

std::shared_ptr<AnimationSequence> PlayerAnimationSet::getShootingSequence(const Direction& direction) {
  if (direction == Direction::North()) {
    std::cout << "Switching to shooting sequence: N" << std::endl;
    return this->getShootingNSequence();
  } else if (direction == Direction::South()) {
    std::cout << "Switching to shooting sequence: S" << std::endl;
    return this->getShootingSSequence();
  } else if (direction == Direction::East()) {
    std::cout << "Switching to shooting sequence: E" << std::endl;
    return this->getShootingESequence();
  } else if (direction == Direction::West()) {
    std::cout << "Switching to shooting sequence: W" << std::endl;
    return this->getShootingWSequence();
  } else if (direction == Direction::NorthEast()) {
    std::cout << "Switching to shooting sequence: NE" << std::endl;
    return this->getShootingNESequence();
  } else if (direction == Direction::SouthEast()) {
    std::cout << "Switching to shooting sequence: SE" << std::endl;
    return this->getShootingSESequence();
  } else if (direction == Direction::SouthWest()) {
    std::cout << "Switching to shooting sequence: SW" << std::endl;
    return this->getShootingSWSequence();
  } else {  // NorthWest
    std::cout << "Switching to shooting sequence: NW" << std::endl;
    return this->getShootingNWSequence();
  }
}

std::shared_ptr<AnimationSequence> PlayerAnimationSet::getShootingNSequence() const { return this->_shootingNSequence; }
std::shared_ptr<AnimationSequence> PlayerAnimationSet::getShootingESequence() const { return this->_shootingESequence; }
std::shared_ptr<AnimationSequence> PlayerAnimationSet::getShootingSSequence() const { return this->_shootingSSequence; }
std::shared_ptr<AnimationSequence> PlayerAnimationSet::getShootingWSequence() const { return this->_shootingWSequence; }
std::shared_ptr<AnimationSequence> PlayerAnimationSet::getShootingNESequence() const {
  return this->_shootingNESequence;
}
std::shared_ptr<AnimationSequence> PlayerAnimationSet::getShootingSESequence() const {
  return this->_shootingSESequence;
}
std::shared_ptr<AnimationSequence> PlayerAnimationSet::getShootingNWSequence() const {
  return this->_shootingNWSequence;
}
std::shared_ptr<AnimationSequence> PlayerAnimationSet::getShootingSWSequence() const {
  return this->_shootingSWSequence;
}
std::shared_ptr<AnimationSequence> PlayerAnimationSet::getIdleSequence() const { return this->_idleSequence; }

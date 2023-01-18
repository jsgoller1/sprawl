#include "RobotAnimationSet.hh"

#include <memory>

#include "AnimationSequence.hh"
#include "Direction.hh"
#include "RobotSpriteManager.hh"

RobotAnimationSet::RobotAnimationSet(const RobotSpriteManager& robotSpriteManager) {
  this->_idle = std::make_shared<AnimationSequence>("idle");
  for (int i = 0; i < 6; i++) {
    this->_idle->addSprite(robotSpriteManager.idle(i));
  }
}

std::shared_ptr<AnimationSequence> RobotAnimationSet::idle() const { return this->_idle; }
std::shared_ptr<AnimationSequence> RobotAnimationSet::movingN() const { return this->_movingN; }
std::shared_ptr<AnimationSequence> RobotAnimationSet::movingE() const { return this->_movingE; }
std::shared_ptr<AnimationSequence> RobotAnimationSet::movingS() const { return this->_movingS; }
std::shared_ptr<AnimationSequence> RobotAnimationSet::movingW() const { return this->_movingW; }
std::shared_ptr<AnimationSequence> RobotAnimationSet::shootingN() const { return this->_shootingN; }
std::shared_ptr<AnimationSequence> RobotAnimationSet::shootingE() const { return this->_shootingE; }
std::shared_ptr<AnimationSequence> RobotAnimationSet::shootingS() const { return this->_shootingS; }
std::shared_ptr<AnimationSequence> RobotAnimationSet::shootingW() const { return this->_shootingW; }

// NOTE: This code has similar versions in Robot and Player, but not completely duplicated
std::shared_ptr<AnimationSequence> RobotAnimationSet::shooting(const Direction& direction) const {
  if (direction == Direction::North()) {
    return this->shootingN();
  } else if (direction == Direction::South()) {
    return this->shootingS();
  } else if (direction == Direction::East() || direction == Direction::SouthEast() ||
             direction == Direction::NorthEast()) {
    return this->shootingE();
  } else {  // West, Southwest, Northwest
    return this->shootingW();
  }
}

std::shared_ptr<AnimationSequence> RobotAnimationSet::dying() const { return this->_dying; }
std::shared_ptr<AnimationSequence> RobotAnimationSet::dead() const { return this->_dead; }

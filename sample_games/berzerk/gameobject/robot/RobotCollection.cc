#include "RobotCollection.hh"

#include "Color.hh"
#include "LevelShootingProxy.hh"
#include "PlayerPositionProxy.hh"
#include "RobotSpriteManager.hh"
#include "Time.hh"

static Color getLevelColor(const int levelNo) {
  switch (levelNo % 10) {
    case 0:
      return Color::Mustard();
    case 1:
      return Color::Red();
    case 2:
      return Color::Cobalt();
    case 3:
      return Color::Green();
    case 4:
      return Color::Magenta();
    case 5:
      return Color::Yellow();
    case 6:
      return Color::White();
    case 7:
      return Color::Pink();
    case 8:
      return Color::Gray();
    case 9:
      return Color::Teal();
  }
  return Color::Orange();
}

RobotCollection::RobotCollection(const int levelNo, const std::vector<Vect2D>& startPositions,
                                 LevelShootingProxy& levelShootingProxy, DrawingProxy& drawingProxy,
                                 PlayerPositionProxy& playerPositionProxy, RobotSpriteManager& robotSpriteManager,
                                 const WallCollisionProxy& collisionProxy, const RobotWallAvoidancePolicy avoidWalls)
    : _robots(std::vector<std::unique_ptr<Robot>>()) {
  robotSpriteManager.setColorMask(getLevelColor(levelNo));

  for (size_t i = 0; i < startPositions.size(); i++) {
    this->_robots.push_back(
        std::unique_ptr<Robot>(new Robot(startPositions.at(i), Vect2D::zero(), levelShootingProxy, drawingProxy,
                                         playerPositionProxy, robotSpriteManager, collisionProxy, avoidWalls)));
  }
}
Robot* RobotCollection::get(const size_t index) const { return this->_robots.at(index).get(); }
size_t RobotCollection::size() const { return this->_robots.size(); }

int RobotCollection::removeMarked() {
  int numberRemoved = 0;
  for (size_t i = 0; i < this->size(); i++) {
    if (this->_robots[i]->getShouldRemove()) {
      this->erase(i);
      numberRemoved++;
    }
  }
  return numberRemoved;
}

void RobotCollection::update(const time_ms deltaT, const bool forceIdle) {
  for (size_t i = 0; i < this->size(); i++) {
    this->_robots[i]->update(deltaT, forceIdle);
  }
}

void RobotCollection::erase(const size_t index) { this->_robots.erase(this->_robots.begin() + (long)index); }

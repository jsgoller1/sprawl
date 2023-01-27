#include "RobotCollection.hh"

#include "LevelShootingProxy.hh"
#include "PlayerPositionProxy.hh"
#include "RobotSpriteManager.hh"
#include "Time.hh"

// RobotCollection::RobotCollection() : _robots(std::vector<std::unique_ptr<Robot>>()) {}

RobotCollection::RobotCollection(const std::vector<Vect2D>& startPositions, LevelShootingProxy& levelShootingProxy,
                                 DrawingProxy& drawingProxy, PlayerPositionProxy& playerPositionProxy,
                                 const RobotSpriteManager& robotSpriteManager)
    : _robots(std::vector<std::unique_ptr<Robot>>()) {
  for (size_t i = 0; i < startPositions.size(); i++) {
    this->_robots.push_back(std::unique_ptr<Robot>(new Robot(startPositions.at(i), Vect2D::zero(), levelShootingProxy,
                                                             drawingProxy, playerPositionProxy, robotSpriteManager)));
  }
}
Robot* RobotCollection::get(const size_t index) { return this->_robots.at(index).get(); }
size_t RobotCollection::size() { return this->_robots.size(); }

void RobotCollection::removeMarked() {
  for (size_t i = 0; i < this->size(); i++) {
    if (this->_robots[i]->getShouldRemove()) {
      this->erase(i);
    }
  }
}

void RobotCollection::update(const time_ms deltaT) {
  for (size_t i = 0; i < this->size(); i++) {
    this->_robots[i]->update(deltaT);
  }
}

void RobotCollection::erase(const size_t index) { this->_robots.erase(this->_robots.begin() + (long)index); }

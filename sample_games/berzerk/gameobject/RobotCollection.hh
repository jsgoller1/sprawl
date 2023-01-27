#pragma once

#include <vector>

#include "GameObjectCollection.hh"
#include "Robot.hh"

// fwd decl
class LevelShootingProxy;
class PlayerPositionProxy;
class RobotSpriteManager;

class RobotCollection : public GameObjectCollection {
 public:
  // TODO: The default constructor here is stinky; there's no reason to create an empty robot collection since we have
  // no insert method (though we could). It exists solely so we can use it in Level's ctor() so RobotCollection can be
  // initialized, then replaced with a correctly constructed one.
  RobotCollection() = default;
  RobotCollection(const std::vector<Vect2D>& startPositions, LevelShootingProxy& levelShootingProxy,
                  DrawingProxy& drawingProxy, PlayerPositionProxy& playerPositionProxy,
                  const RobotSpriteManager& robotSpriteManager);
  Robot* get(const size_t index) override;
  size_t size() override;

  void update(const time_ms deltaT);
  void removeMarked();

 private:
  std::vector<std::unique_ptr<Robot>> _robots;

  void erase(const size_t index);
};

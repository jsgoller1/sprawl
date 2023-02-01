#pragma once

#include <vector>

#include "Bullet.hh"
#include "GameObjectCollection.hh"
#include "Time.hh"

class BulletCollection : public GameObjectCollection {
 public:
  BulletCollection(const int levelNo, BulletSpriteManager& bulletSpriteManager, DrawingProxy& drawingProxy);
  Bullet* get(const size_t index) override;
  size_t size() override;

  void createAt(const Direction& direction, const Vect2D& origin);
  void removeMarked();
  void update(const time_ms deltaT);

 private:
  std::vector<std::unique_ptr<Bullet>> _bullets;
  DrawingProxy& _drawingProxy;
  BulletSpriteManager& _bulletSpriteManager;

  void erase(const size_t index);
};

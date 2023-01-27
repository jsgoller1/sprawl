#include "BulletCollection.hh"

BulletCollection::BulletCollection(const BulletSpriteManager& bulletSpriteManager, DrawingProxy& drawingProxy)
    : _bullets(std::vector<std::unique_ptr<Bullet>>()),
      _drawingProxy(drawingProxy),
      _bulletSpriteManager(bulletSpriteManager) {}

Bullet* BulletCollection::get(const size_t index) {
  // NOTE: We intentionally do not do bounds checking here; rather than returning a nullptr when an invalid
  // index is passed to this function (then having to trace that nullptr back to this function), I'd rather
  // just loudly get a std::out_of_range here.
  return this->_bullets.at(index).get();
}
size_t BulletCollection::size() { return this->_bullets.size(); }

void BulletCollection::createAt(const Direction& direction, const Vect2D& origin, const BulletColor color) {
  this->_bullets.push_back(
      std::unique_ptr<Bullet>(new Bullet(origin, direction, this->_drawingProxy, this->_bulletSpriteManager, color)));
}

void BulletCollection::removeMarked() {
  for (size_t i = 0; i < this->size(); i++) {
    if (this->_bullets[i]->getShouldRemove()) {
      this->erase(i);
    }
  }
}

void BulletCollection::update(const time_ms deltaT) {
  // NOTE: A little smelly, but bullets don't need the time
  // since it's a static animation
  (void)deltaT;
  for (size_t i = 0; i < this->size(); i++) {
    this->_bullets[i]->update();
  }
}

void BulletCollection::erase(const size_t index) { this->_bullets.erase(this->_bullets.begin() + (long)index); }

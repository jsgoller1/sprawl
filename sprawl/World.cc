#include "World.hh"

/*
 * Originally, we were testing if an object goes off the screen in PositionComponent. Instead, we should have each World
 * own a WorldFence object or something. In Unity, there is no (to my knowledge) inherent limit on the world size;
 * instead, the player must construct boundaries and a skybox to keep the player inside a play area, and kill them if
 * they leave. We should follow suit, but make it easy to keep the player in the boundary area.
 *
 * Original bounding code:
 *   bool PositionComponent::validPosition(const Vect2D& position) {
 *     return (-SCREEN_WIDTH / 2 <= position.x()) && (position.x() <= SCREEN_WIDTH / 2) &&
 *            (-SCREEN_HEIGHT / 2 <= position.y()) && (position.y() <= SCREEN_HEIGHT / 2);
 *   }
 */

World::World(const std::shared_ptr<Zone> currentZone) {
  // TODO: I really don't want World to know anything about JSON, and instead
  // would rather have WADLoader just do things via calls (e.g. initLogging(),
  // no need to pass json to it) or return actual objects like Character. This
  // will do for now.
  this->currentZone = currentZone;
}

void World::gameLoopUpdate(const std::shared_ptr<GameLoopInputEvents> inputEvents, const time_ms duration) {
  this->currentZone->gameLoopUpdate(inputEvents, duration);
}

std::shared_ptr<std::vector<std::shared_ptr<DrawingComponent>>> World::getDrawables() const {
  return this->currentZone->getDrawables();
}

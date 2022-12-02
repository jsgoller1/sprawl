#pragma once

#include "Background.hh"
#include "DrawingComponent.hh"
#include "GameAction.hh"
#include "GameObject.hh"
#include "InputHandler.hh"
#include "Logging.hh"
#include "PhysicsManager.hh"
#include "PositionComponent.hh"
#include "Texture.hh"
#include "Types.hh"

// Forward declaration
class WADLoader;

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

class World {
  /*  // Keeps track of the interactive game world state, e.g. which
  // Characters, Worlds, and GameObjects exist in the world. World knows if an
  // GameObject should be drawn, but not how to draw it (Screen knows how).
  // NOTE: World implements an MVC Model
  // NOTE: Menus, UI, dialogue boxes, etc should not be part of the world

   * A World is a location in the World containing GameObjects.
   * TODO: Initially, all zones are rectangular, have the same height as the window, and every part of them
   * should be drawn on the screen. Eventually, we'll want to be able to scroll around in them.
   */
 public:
  World();
  virtual ~World();
  std::shared_ptr<Background> getBackground() const;
  void setBackground(const std::shared_ptr<Background> background);
  std::shared_ptr<PhysicsManager> getPhysicsManager() const;
  void setPhysicsManager(const std::shared_ptr<PhysicsManager> physicsManager);
  std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> getGameObjects() const;
  void setGameObjects(const std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects);
  void addGameObject(const std::shared_ptr<GameObject> gameObject);

  // TODO: serialize(); // needed for saving game and level editor
  virtual std::shared_ptr<std::vector<std::shared_ptr<DrawingComponent>>> getDrawables() const;

  void gameLoopUpdate(const std::shared_ptr<GameLoopInputEvents> inputEvents, const time_ms duration);

 private:
  // We only need to care about physics and AI going on in currentWorld,
  // since only currentWorld will have active GameObjects. Additionally, physics
  // might differ based on zone (underwater, outer space, cyberspace, etc)
  // TODO: Do we need getters and setters for these attributes? Unlikely, but
  // possible if managers within the World need to talk to each other. Don't need
  // them presently.
  std::shared_ptr<Background> background;
  std::shared_ptr<PhysicsManager> physicsManager;

  // TODO: Since GameObjects have a unique ID, we should be able to insert them into
  // a set. Furthermore, we might not even need a distinct GameObject collection if we make
  // just forward to the EntityManager. We need to resolve "who owns game objects?"
  std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects;

  virtual void handleInput(const std::shared_ptr<GameLoopInputEvents> inputEvents) = 0;
};

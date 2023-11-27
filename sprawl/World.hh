#pragma once

#include <memory>
#include <vector>

#include "DrawingManager.hh"
#include "GraphicsSettings.hh"
#include "Math.hh"
#include "PhysicsManager.hh"
#include "Types.hh"

// Forward declaration
class DrawingManager;
class GameObject;
class GameLoopInputEvents;
class PhysicsManager;
class WADLoader;

/*
 * Originally, we were testing if an object goes off the screen in PositionComponent. Instead, we should have each
 * World own a WorldFence object or something. In Unity, there is no (to my knowledge) inherent limit on the world
 * size; instead, the player must construct boundaries and a skybox to keep the player inside a play area, and kill
 * them if they leave. We should follow suit, but make it easy to keep the player in the boundary area.
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
  World(const GraphicsSettings& screenParameters);
  ~World();
  PhysicsManager& getPhysicsManager();
  void setPhysicsManager(const PhysicsManager& physicsManager);
  std::vector<std::shared_ptr<GameObject>>& getGameObjects();
  void addGameObject(const std::shared_ptr<GameObject> gameObject);

  void gameLoopUpdate(const time_ms duration);

 private:
  // We only need to care about physics and AI going on in currentWorld,
  // since only currentWorld will have active GameObjects. Additionally, physics
  // might differ based on zone (underwater, outer space, cyberspace, etc)
  // TODO: Do we need getters and setters for these attributes? Unlikely, but
  // possible if managers within the World need to talk to each other. Don't need
  // them presently.
  PhysicsManager physicsManager = PhysicsManager();

  // TODO: Because of SDL behavior, we cannot currently double-init the drawing manager.
  DrawingManager drawingManager;

  // TODO: Since GameObjects have a unique ID, we should be able to insert them into
  // a set. Furthermore, we might not even need a distinct GameObject collection if we make
  // just forward to the EntityManager. We need to resolve "who owns game objects?"
  std::vector<std::shared_ptr<GameObject>> gameObjects;
};

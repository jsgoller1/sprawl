#pragma once

#include "Background.hh"
#include "Character.hh"
#include "DrawingComponent.hh"
#include "GameAction.hh"
#include "GameObject.hh"
#include "InputHandler.hh"
#include "Logging.hh"
#include "PhysicsManager.hh"
#include "Platform.hh"
#include "PositionComponent.hh"
#include "Texture.hh"
#include "Types.hh"

// Forward declaration
class WADLoader;

/*
 * A Zone is a location in the World containing GameObjects.
 * TODO: Initially, all zones are rectangular, have the same height as the window, and every part of them should be
 * drawn on the screen. Eventually, we'll want to be able to scroll around in them.
 */
class Zone {
 public:
  Zone();

  // TODO: serialize(); // needed for saving game and level editor
  void setGravityConstant(const real gravityConstant);
  void setBackground(const std::shared_ptr<Background> background);
  void addPlayerCharacter(const std::shared_ptr<Character> playerCharacter);
  void addGameObject(const std::shared_ptr<GameObject> gameObject);

  void gameLoopUpdate(const std::shared_ptr<GameLoopInputEvents> inputEvents, const time_ms duration);
  std::shared_ptr<std::vector<std::shared_ptr<DrawingComponent>>> getDrawables() const;

 private:
  // We only need to care about physics and AI going on in currentZone,
  // since only currentZone will have active GameObjects. Additionally, physics
  // might differ based on zone (underwater, outer space, cyberspace, etc)
  // TODO: Do we need getters and setters for these attributes? Unlikely, but
  // possible if managers within the Zone need to talk to each other. Don't need
  // them presently.
  std::shared_ptr<PhysicsManager> physicsManager;
  std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects;
  std::shared_ptr<Background> background;
  std::shared_ptr<Character> player;

  void handleInput(const std::shared_ptr<GameLoopInputEvents> inputEvents);
};

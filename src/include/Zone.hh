/*
 * A Zone is a location in the World containing GameObjects
 * TODO: Initially, all zones are rectangular, have the same height as the
 * window, and every part of them should be drawn on the screen. Eventually,
 * we'll want to be able to scroll around in them.
 */

#pragma once

#include "Background.hh"
#include "Character.hh"
#include "DrawingComponent.hh"
#include "GameAction.hh"
#include "GameObject.hh"
#include "Logger.hh"
#include "Memory.hh"
#include "PhysicsManager.hh"
#include "Platform.hh"
#include "PositionComponent.hh"
#include "Texture.hh"
#include "Types.hh"

// Forward declaration
class WADLoader;

class Zone {
 public:
  Zone();

  // TODO: serialize(); // needed for saving game and level editor
  void setBackground(const shared_ptr<Background> background);
  void addPlayerCharacter(const shared_ptr<Character> playerCharacter);
  void addGameObject(const shared_ptr<GameObject> gameObject);

  void gameLoopUpdate(const GameAction& action, const time_ms duration);
  shared_ptr<vector<shared_ptr<DrawingComponent>>> getDrawables() const;

 private:
  // We only need to care about physics and AI going on in currentZone,
  // since only currentZone will have active GameObjects. Additionally, physics
  // might differ based on zone (underwater, outer space, cyberspace, etc)
  // TODO: Do we need getters and setters for these attributes? Unlikely, but
  // possible if managers within the Zone need to talk to each other. Don't need
  // them presently.
  shared_ptr<PhysicsManager> physicsManager;
  shared_ptr<vector<shared_ptr<GameObject>>> gameObjects;
  shared_ptr<Background> background;
  shared_ptr<Character> player;

  void handleInput(const GameAction& action);
};

#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Singleton.hh"
#include "Types.hh"

// Forward declaration
class Actor;
class DrawingManager;
class GameLoopInputEvents;
class WADLoader;

class ActorManager : public Singleton<ActorManager> {
  /*
   * ActorManager is the single source of truth for all Actors. It knows what Zones they belong in, whether they are
   * alive, and when to destroy them. Actors cannot be created or destroyed except via ActorManager::createActor() and
   * ActorManager::destroyActor().
   */

 public:
  std::shared_ptr<Actor> createActor(const EntityName name, const SceneID sceneID);
  void destroyActor(std::shared_ptr<Actor> actor);
  void destroyActor(UUID uuid);

  void activateScene(const SceneID sceneID);
  void deactivateScene(const SceneID sceneID);
  std::unordered_set<SceneID> getActiveScenes() const;

 private:
  friend Singleton<ActorManager>;

  ActorManager() = default;
  ActorManager(const ActorManager&) = delete;
  ActorManager& operator=(const ActorManager&) = delete;
  ActorManager(ActorManager&&) = delete;
  ActorManager& operator=(ActorManager&&) = delete;

  // actors is the single source of truth about all actors; actor data should never
  // exist outside of this map.
  std::unordered_map<UUID, std::shared_ptr<Actor>> actors = {};

  // sceneActors is a map of scene IDs to a set of actors that are in that scene.
  // actors may be in multiple scenes. A special global scene is reserved for actors
  // that are active in every scene (e.g. actors that would have global game logic attached to them).
  std::unordered_map<SceneID, std::unique_ptr<std::unordered_set<UUID>>> sceneActors = {};

  // activeScenes is a set of scene IDs that are currently active. Actors in these scenes are enabled by default
  // unless they are disabled.
  std::unordered_set<SceneID> activeScenes = {};
};

#include "ActorManager.hh"

#include <memory>

#include "Actor.hh"

std::shared_ptr<Actor> ActorManager::createActor(const EntityName name, const std::vector<SceneID>& sceneIDs) {
  // NOTE: This is a lambda that will be called when the shared_ptr is destroyed. It is implemented
  // because Actor's destructor is intentionally private (only ActorManager is allowed to create or
  // destroy Actors), so shared_ptr can't use it.
  auto actorDeleter = [](Actor* ptr) { delete ptr; };
  std::shared_ptr<Actor> actor(new Actor(name), actorDeleter);

  this->actors.emplace(std::make_pair(actor->getUUID(), actor));
  for (const auto& sceneID : sceneIDs) {
    auto sceneActorsIt = sceneActors.find(sceneID);
    if (sceneActorsIt == sceneActors.end()) {
      sceneActors[sceneID] = std::make_unique<std::unordered_set<UUID>>();
      sceneActorsIt = sceneActors.find(sceneID);
    }
    sceneActorsIt->second->emplace(actor->getUUID());
  }
  return std::shared_ptr<Actor>(actor);
}

void ActorManager::destroyActor(std::weak_ptr<Actor> actor) {
  if (actor.expired()) {
    return;
  }
  std::shared_ptr<Actor> actor_shared = actor.lock();
  UUID uuid = actor_shared->getUUID();
  actors.erase(uuid);
  for (auto& sceneToActors : sceneActors) {
    sceneToActors.second->erase(actor_shared->getUUID());
  }
}

void ActorManager::destroyActor(UUID uuid) {
  std::weak_ptr<Actor> actor = actors.at(uuid);
  destroyActor(actor);
}

void ActorManager::activateScene(const SceneID sceneID) {
  auto sceneActorsIt = sceneActors.find(sceneID);
  if (sceneActorsIt == sceneActors.end()) {
    return;
  }
  for (auto& actorUUID : *sceneActorsIt->second) {
    std::shared_ptr<Actor> actor = actors.at(actorUUID);
    actor->setEnabled(true);
  }
  this->activeScenes.insert(sceneID);
}

void ActorManager::deactivateScene(const SceneID sceneID) {
  auto sceneActorsIt = sceneActors.find(sceneID);
  if (sceneActorsIt == sceneActors.end()) {
    return;
  }
  for (auto& actorUUID : *sceneActorsIt->second) {
    std::shared_ptr<Actor> actor = actors.at(actorUUID);
    actor->setEnabled(false);
  }
  this->activeScenes.erase(sceneID);
}

std::unordered_set<SceneID> ActorManager::getActiveScenes() const { return this->activeScenes; }

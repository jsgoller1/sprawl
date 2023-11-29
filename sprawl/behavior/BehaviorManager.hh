#pragma once

#include "ComponentManager.hh"
#include "Singleton.hh"

class BehaviorManager : public ComponentManager, public Singleton<BehaviorManager> {
 public:
  void gameLoopUpdate(time_ms duration) override;

 private:
  friend class Singleton<BehaviorManager>;
  BehaviorManager();
  BehaviorManager(const BehaviorManager&) = delete;
  BehaviorManager& operator=(const BehaviorManager&) = delete;
};

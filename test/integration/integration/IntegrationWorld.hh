#pragma once

#include "Character.hh"
#include "World.hh"

class IntegrationWorld : public World {
 public:
  void addPlayerCharacter(const std::shared_ptr<Character> playerCharacter);
  std::shared_ptr<std::vector<std::shared_ptr<DrawingComponent>>> getDrawables() const override;

 private:
  std::shared_ptr<Character> playerCharacter;

  void handleInput(const std::shared_ptr<GameLoopInputEvents> inputEvents) override;
};

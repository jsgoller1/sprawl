#include "Paddle.hh"
#include "World.hh"

class GameStateFSM {
  /*
   * Really don't even need this class for now, can do all state transitions in game code with variables
   * for MVP, then refactor it to engine code with an FSM driver that can be generically used
   * Game states:
   * - Waiting: Player must press space to start
   * - Playing: ball is in motion back and forth
   * - Finished: score has reached N, win/lose message displayed
   * - Quitting: game is over, shutting down
   */
};

class PorngWorld : public World {
 public:
  void setPlayerPaddle();
  std::shared_ptr<Paddle> getPlayerPaddle();
  void setAIPaddle();
  std::shared_ptr<Paddle> getAIPaddle();

 private:
  void handleInput(const std::shared_ptr<GameLoopInputEvents> inputEvents) override;
  std::shared_ptr<Paddle> _playerPaddle;
  std::shared_ptr<Paddle> _aiPaddle;
};

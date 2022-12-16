#include "Paddle.hh"
#include "World.hh"

// class GameStateFSM {
/*
 * Really don't even need this class for now, can do all state transitions in game code with variables
 * for MVP, then refactor it to engine code with an FSM driver that can be generically used
 * Game states:
 * - Waiting: Player must press space to start
 * - Playing: ball is in motion back and forth
 * - Finished: score has reached N, win/lose message displayed
 * - Quitting: game is over, shutting down
 */
// };

enum GameState {
  BETWEEN_MATCHES,
  BETWEEN_ROUNDS,
  ROUND_ONGOING,
  QUITTING,
};

// Forward decls
class GameLoopInputEvents;

class PorngWorld : public World {
 public:
  PorngWorld(const GraphicsSettings& screenParameters);
  void setPlayerPaddle(const std::shared_ptr<Paddle> aiPaddle);
  Paddle& getPlayerPaddle();
  void setAIPaddle(const std::shared_ptr<Paddle> aiPaddle);
  Paddle& getAIPaddle();
  void gameLoopUpdate(const std::shared_ptr<GameLoopInputEvents> inputEvents, const time_ms duration) override;

 private:
  std::shared_ptr<Paddle> _playerPaddle;
  std::shared_ptr<Paddle> _aiPaddle;
  GameState currentState = BETWEEN_MATCHES;

  void handleInput(const std::shared_ptr<GameLoopInputEvents> inputEvents) override;
  void behaviorBetweenMatches();
  void behaviorBetweenRounds();
  void behaviorRoundOngoing();
};

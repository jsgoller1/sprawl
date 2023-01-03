#include "Player.hh"

#include "PlayerSpriteManager.hh"

#define PLAYER_DEFAULT_HEIGHT 100
#define PLAYER_DEFAULT_WIDTH 30

PlayerAnimationSet::PlayerAnimationSet(const PlayerSpriteManager& playerSpriteManager) {
  std::shared_ptr<AnimationSequence> idleSequence =
      std::make_shared<AnimationSequence>(std::vector<std::shared_ptr<Sprite>>{playerSpriteManager.standing()});

  this->_animations = std::map<PlayerState, std::shared_ptr<AnimationSequence>>{
      {IDLE, idleSequence},   {MOVING_W, nullptr},    {MOVING_E, nullptr},    {SHOOTING_N, nullptr},
      {SHOOTING_E, nullptr},  {SHOOTING_S, nullptr},  {SHOOTING_W, nullptr},  {SHOOTING_NE, nullptr},
      {SHOOTING_SE, nullptr}, {SHOOTING_NW, nullptr}, {SHOOTING_SW, nullptr}, {DYING, nullptr},
  };
}
std::shared_ptr<AnimationSequence> PlayerAnimationSet::getAnimation(const PlayerState& state) {
  return this->_animations[state];
}

Player::Player(const Vect2D& position, const Vect2D& velocity, ShootingProxy& shootingProxy, DrawingProxy& drawingProxy,
               const PlayerSpriteManager& playerSpriteManager)
    : GameObject(position, velocity),
      IShooting(shootingProxy),
      IAnimatedDrawing(this->getPositionComponent(), PLAYER_DEFAULT_HEIGHT, PLAYER_DEFAULT_WIDTH, drawingProxy,
                       nullptr) {
  this->_playerAnimationSet = std::unique_ptr<PlayerAnimationSet>(new PlayerAnimationSet(playerSpriteManager));
  this->setAnimationSequence(this->_playerAnimationSet->getAnimation(PlayerState::IDLE));
}

void Player::resolveCollision(GameObject& target) { (void)target; }

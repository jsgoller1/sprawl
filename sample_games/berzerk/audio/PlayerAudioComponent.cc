#include "PlayerAudioComponent.hh"

#include "Configs.hh"

PlayerAudioComponent::PlayerAudioComponent() : _playerShooting(Mix_LoadWAV(DEFAULT_PLAYER_SHOOTING_SOUND_PATH)) {}

void PlayerAudioComponent::playShooting() { this->playSound(this->_playerShooting); }

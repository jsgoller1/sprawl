#pragma once

#include "AudioComponent.hh"

class PlayerAudioComponent : public AudioComponent {
 public:
  PlayerAudioComponent();
  void playShooting();

 private:
  Mix_Chunk* _playerShooting;
};

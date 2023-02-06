#pragma once

#include "SDL2/SDL_mixer.h"

class AudioComponent {
  AudioComponent();
  void playSound(Mix_Chunk const *sound);
};

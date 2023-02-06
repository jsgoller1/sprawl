#pragma once

#include "SDL2/SDL_mixer.h"

class AudioComponent {
 protected:
  void playSound(Mix_Chunk* sound);
};

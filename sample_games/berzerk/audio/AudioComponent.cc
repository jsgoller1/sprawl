#include "AudioComponent.hh"

void AudioComponent::playSound(Mix_Chunk* sound) { Mix_PlayChannel(-1, sound, 0); }

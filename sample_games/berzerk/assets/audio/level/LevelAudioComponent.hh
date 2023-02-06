#pragma once

#include "AudioComponent.hh"

class LevelAudioComponent : public AudioComponent {
 public:
  LevelAudioComponent();
  void playRandomRobotSpeech() const;
  void playIntruderAlert() const;
  void playPlayerKilled() const;
  void playBravePlayerExit() const;
  void playCowardlyPlayerExit() const;
};

#pragma once

#include "Math.hh"

typedef struct GraphicsSettings {
  ScreenWidth screenWidth = 0;
  ScreenHeight screenHeight = 0;
  bool useHardwareAcceleration = true;
  bool useVSync = true;
} GraphicsSettings;

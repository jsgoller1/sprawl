# Textures and Rendering 

Current origin/main: dc2cf4898d9d64bcb193918377666bc1a93f81c5

## Problem
- Add background texture (assets/world-background.bmp)
- Add player texture (assets/player.bmp)
- Add enemy texture (assets/enemy.bmp)
- Add wall-indestructible textures across floor in platform shape (assets/wall-indestructible.bmp)

## Notes
- Can I use `IMG_LoadTexture()`? Do I need to create a temporary surface?

## Plan
- Implement Texture class, each object has one
- Implemente Renderer class, Screen has one

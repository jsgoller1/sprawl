# Functional Spec - V0.1 (MVP)

## Goal / Gameplay
- Platformer
- Survive as long as possible; one hit kill on enemies and player.
- Enemies become more numerous, move faster, and shoot faster as time goes on (capped)
- Bullets also fly faster (capped)
- Player gets 50 points for killing an enemy

## World
- Art: https://itch.io/queue/c/2053292/cyberpunk-pixel-art?game_id=1609957
- Single fixed size play space, no scrolling
- Only gameplay surfaces are platforms and ladders 

## Character
- Art: https://www.gamedevmarket.net/asset/pixel-cyborg-killer-01/
- Animations (provided by art)
- Single choice
- Shooting functionality

## Enemies
- Art: https://www.gamedevmarket.net/asset/pixel-minotaur-demon-asset/
- Animations (provided by art)
- Single type with shooting behavior
- Randomly wanders around the map until player intersects with cardinal direction
    - Pathfinding via A* search
- Shoots at player as soon as they intersect
- Walks to player's last seen position, then goes to wandering again (unless it spots player again)

## Music
- Loop 
- Ask Bernie if he wants to collab
- Placeholder: reached out to [Shen / jk247](https://jaykay47.bandcamp.com/album/cyberpunk) 

## Sounds
- Shooting sounds:
    - https://www.gamedevmarket.net/asset/laser-shots-and-reload-sounds/
    - https://www.gamedevmarket.net/asset/sci-fi-weapons-sound-pack-2/
- Explosions
- Collisions
- Walking ambient





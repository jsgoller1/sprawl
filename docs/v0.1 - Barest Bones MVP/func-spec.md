# v0.1 - Barest Bones MVP
## Plan
Literally the bare minimum necessary to "play"

### Player
A blue box
- Player can move and jump with W/A/D
- Directional shooting with arrows

### World
- Single grey platform
- Blank background image

### Enemies 
Red box
- Enemy moves back and forth on platform, jumping at random
- Enemy shoots in player's direction based on line casts in U/L/R directions if intersection occurs
- Enemy also shoots randomly 

### Win / loss
Game ends if player bullet hits enemy or if enemy bullet hits player

## Retrospective
I implemented everything here except for shooting, enemy movement, and the win/lose condition. I had spent
most of the time on loading textures, movement, and collisions. Shooting will now be relatively simple: just
draw a box with velocity in the given direction, have it move until it reaches the screen edge, and if it collides with anything, remove that object. 

However, the current physics system sucks and is very janky - collisions don't work very well, gravity is a little odd, double jumping isn't supported, etc. Some work here will make later features easier to work with, I think. 

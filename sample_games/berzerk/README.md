Berserk
---
This version of berserk is my second design. It is meant to be as faithful to the original as possible. I couldn't find the source code, so the game behavior is based on observations 
after playing it for around an hour. You can play the original version [here](https://archive.org/details/arcade_berzerk).
## Gameplay
- Score is initialized to 0
- Lives initialized to 3
    - Free lives are awarded at 5k and 10k points. 
- Level are initialized to 1
- Each robot color has two levels (except the first one); this is not faithful to the original but it is simpler and won't really affect gameplay. 
- Player spawns, flashes for a second, then the game begins
- Robots move around and attempt to attack the player
- Touching the walls or a bullet kills any character (except evil Otto)
- Level counter is incremented if player kills all robots and flees. 
- Being killed or fleeing the level before all robots are dead does not increment the level counter.
- Each level has a base speed value. It is a base value that increases as robot color changes, and per level as robots die. This speed value is used across the game for robot speed, evil otto speed, etc.  
- When a player flees, the entire board turns monochrome and shifts in the opposite direction they fled in. 

## Game Board
- The berzerk gameboard is a 3x5 grid of cells; the cells share walls, so there are 3 rows of 6 possible vertical walls, and 4 rows of 5 possible horizontal walls. 
- The 16 outermost walls (5 top horizontal, 5 bottom horizontal, 3 left vertical, 3 right vertical) are "border walls" and are always drawn and always dark blue, 
  EXCEPT for the middle wall of each border, which is an "exit". On some levels, all 4 exits are not drawn. On others, the one closest to the player's starting position is drawn
  but shaded with the color of the robots for that level.
- On each level, 7 or 8 internal walls are drawn. 
- Unless an exit is blocked by a robot-colored wall, every exit can be reached from every point of grid; internal walls are never drawn such that an exit cannot be reached.
- Internal walls are occasionally drawn so that they completely enclose an area of the board and prevent any characters from entering or exiting it; the player is never spawned in
  such an enclosure.
- Since walls will always appear at the same locations (and levels differ only by layouts), we can just use constants for where each wall should appear and how thick they should be,
  then draw SDL_Rects around those. 
### Board generation procedure
This procedure will generate the playing space:
1. Draw all border walls, excluding exits. 
1. Assign a unique label to each each contiguous group of border walls, say numbers 1 through 4. Assign to each individual wall the number of the group it belongs to. 
1. While fewer than 8 internal walls exist, loop continuously over each possible location of an internal wall and do the following:
    1. Randomly determine if a wall should exist here; if not, go to the next location.
    1. Place a wall in this location. Switch based on how many walls it is connected to at its vertices (in total):
        - 0: Label the wall "F" for "floating group" 
        - 1: Label the wall with the same label as the wall it is connected to.
        - 2 or more:
            - If every connected wall has the same label, assign that label to this wall.
            - Otherwise, remove the wall at this location. 
1. If the previous level ended with the player passing through an exit, initialize them at the exit opposite to this one, and block it with a robot colored wall.
1. Else, place the player randomly in front of one of the four exits and do not block any exits. 
1. Randomly place the robots across the game board (no two robots should begin overlapping)

## Robots
### States and animation
- Robots can have simple states, but it should only control which sprite sequence is used for their animations:
 - MOVING, STANDING, and DYING
### Combat
- Robots wait for 1-2 seconds after the player spawns before attacking (unless the player starts moving). 
- Robots will fire at the player whenever they have the same X or Y coordinate as the player, or can reach them from a diagonal. 
- Robots will fire regardless of walls blocking them from hitting the player
- Robots will shoot each other
- All robots must be dead for the player to advance to the next level.
    - Fleeing before all robots are dead repeats the level.
- The original game had an increasing limit of robot-generated bullets that could be on the screen at once. 
### Navigation
The original robots appear to move so that they match the player's X and Y coordinates. They do not do intelligent pathfinding to get closer to the player. It is not clear
exactly how they decide what direction to move in, or when not to walk into a wall. 
- A few robots will sometimes just sit idle; other times they all move together. 
- Robots will sometimes walk into walls and other times hold short of a wall. 
- Robots pick a heading (from 8 compass directions) that will bring them closer to the player.
    - They can pick a random heading, or whichever (of several) will close their closest axis to the player's.
    - The robots then move along it until they can fire. 
    - They pick new headings each time the player intersects with their firing direction. 
    - Starting on level 2, robots will have a severely decreased chance of walking into a wall
        - Maybe something like "if the next move would walk into a wall, do not move further on this heading." and reset on new headings?
        - Could also have a randomly set bool for "willing to walk into a wall".  
- Robots never try to move further from the player.  
### Speed
- Robot movement, firing rate, and animation speed increases as fewer robots remain. 
### Other
- Robots on level 1 do not shoot at the player

## Evil Otto
- Evil Otto initializes from the player's starting position after a countdown has reached zero.
- Evil Otto moves linearly towards the player while doing a jumping animation; his hitbox only exists around his face even though the entire sprite covers
  the jumping path. 
- Otto moves at half speed if there are robots on the screen

## Progressive Feature plan
1. Game space loads with pre-determined wall layout
1. Character and Robots load at predetermined locations
1. Character can move around
1. Character dies if they touch wall or robot
1. Lives mechanic
1. Character wins if they reach exit
1. Character can shoot one projectile at a time 
1. Sounds on shooting
1. Bullets stop if they hit wall or robot
1. Robots die if they are hit by bullet
1. Robot shoot back if character intersects shooting axis
1. Player dies if hit by bullet
1. Robots can navigate from one place to another without hitting walls or (usually) hitting each other
1. Animations for robots and player
1. Robots "detect" player through walls and seek them out
1. Randomized level layouts
1. Lives UI
1. Random robot sounds
1. Bonus lives if all robots killed
1. Level is completed on exit; entire screen holds and is scrolled, then new level is loaded
1. Evil Otto appears on timer, with "intruder alert"
1. New levels have color with robots
1. Scaling robot difficulty - detection distance
1. Scaling robot difficulty - movement speed
1. Scaling robot difficulty - firing rate / projectile speed
1. Scaling robot difficulty - no friendly fire
1. Scaling robot difficulty - walking into walls 

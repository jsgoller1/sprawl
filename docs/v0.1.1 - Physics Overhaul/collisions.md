# Collisions

## Background
- Collisions in Sprawl are nonconcurrent/sequential; each object's movement is individually tested. We never have to deal with "two objects moving at the same time";a collision only occurs when a single **source object** collides with **target objects** (one or several). 
- Most source objects are unlikely to collide with more than 3 or 4 target objects as the result of a move; this could happen if the source object is significantly larger than the target object.
- All collisions in Sprawl are detected by testing the intersection of rectangular bounding boxes around each object. 
- All objects in Sprawl are rigid bodies. 


### Possible situations
Suppose we have the following types of objects:
- A character (force responsive and moving)
- A moving platform (unresponsive and moving)
- A wall (unresponsive and stationary)
 
Now consider the following:
- Character 1 collides with Character 2
    - Character 1
    - Character 2
    - Collision type: Elastic 
        - Total momentum is preserved
- Character collides with a wall
    - Wall
        - May recieve force, but nothing will happen
        - No change in movement
    - Character
        - Moves as close to wall as possible
        - If any movement along the non-collision axis can occur, it does
        - If the wall applies any force to the character, it is just enough to zero the character's x-velocity. Computing this will be hard, 
          and we may be better served by just directly zeroing the velocity.
    - Collision type: Inelastic
        - The total momentum is lost because velocity along the collision axis was zeroed. 
- Character collides with moving platform
    - Same as collision with a stationary wall. 
- Moving platform collides with a character
    - Platform 
        - Moves as close to character as possible
        - May recieve force from character, but nothing will happen
    - Character
        - The platform should push the character in the direction it's moving in
            - If the character is stationary, its velocity becomes the same as the platform's 
            - If the character is in motion, then any velocity it has opposite the platform's direction is cancelled, but in other directions can be resolved inelastically 
                - Although as soon as the character's movement is checked, this will happen anyway.         
            - If the platform needs to move and can't, it could result in Mario / Streets of Rogue crush-deaths / destruction. 
    - Collision type: Neither ("quasi-elastic"?)
        - the character is moved elastically
        - forces on the platform have no effect; momentum not preserved
- Moving platform collides with moving platform or wall
    - Neither applies force to the other
    - Neither may continue in its direction if moving

## Collision testing
- We should try moving along both axes at once to determine all "true" collisions. 
    - For elastic collisions, we don't need to worry about directions; we can just swap velocities (or apply forces that will have the same effect)
    - For inelastic collisions, we can determine "which" axis caused the collision by testing moves along each one individually
        - Single axis moves are trivial and require no further testing 
        - If we collide with an object when doing an x,y move and also an x move, it means the x-axis movement caused the collision.
        - We don't need to care about anything that only occurs during an x-only test of an x,y move. 
    - The CollisionTestResult only needs to return the closest object if we collide with several at different distances along the same axis (or closest ones, if several are equal distance from us along that axis)

## Collision resolution
- I don't know whether it'd be better to try to do everything with forces, or just swap velocities. For now, let's assume we apply forces.
- Some ugly code here is OK at first; would rather get this working than looking clean initially 
- All collisions
    - We need to move as close as possible to the object we collide with
    - can implement a CollisionComponent::getClosestMove() or something
    - If we collide with multiple objects and should apply force to targets, we're just going to apply the same force to all of them and their cumulative force back on us
        - Fine for elastic, and for all others it won't matter
- Elastic
    - Source and target apply forces to each other proportional to their velocities
- Inelastic
    - Source's velocity along collision axis is zeroed;
    - We don't need to try to continue moving it along the other axis, as the remaining velocity will be applied during the next test
        - This will be not-completely-correct, but probably unnoticeably so (and much easier to implement)
- Partial elastic
    - We can probably resolve this using the same code as elastic, since the forces applied to the source won't have an effect
- Pseudo
    - Source's velocity should be zeroed along collision axis; no forces will be applied either way. 



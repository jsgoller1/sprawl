## Points and vectors
We should have three separate classes/types:
- Point: this is a 2D value that represents either a screen location, or a direction
- Magnitude: this is a dimensionless (?) value
- Force: this is a composition of a Point and Magnitude; it represents a force of a particular magnitude in the direction of the point. 


## Better collisions, velocities, and gravity
### Problem
The current way of managing gravity completely sucks and results in janky-ass behavior.

### Thoughts
- Every object should have a "force" value indicating which direction / magnitude force is being applied to it
- Presently, we will assume the magnitude of a force describes how far the object moves in that direction if no collision
occurs; I think this means "unit mass in a frictionless vacuum", but I could be wrong. 
    - Later on, we can add friction and air/water resistance
- Collisions should be directional; if movement occurs in the x and y direction but an x-direction collision
happens, only the x velocity needs to be zeroed.
- To keep things simple, we should just think of four cardinal directions, and only get more complicated if necessary. 
- Gravity should add downward force (up to a limit, beyond which extra acceleration could happen if the character has a means of creating it)
- Each frame, objects should move according to their velocity; we should not try to move them directly except 
for things like teleporting. 
- Movements should be predictive / reversible: as part of applying velocity, we should attempt to move
  the object, see if a collision ensues, and then reverse it if so. 
- Horizontal movement in mid-air is allowed; pretty common for platformers
- Double jumping is allowed (or even multi-jumping, could be upgradable)

Scenarios for any object:
- Gravity
    - Object on surface (downward collision in range) -> no velocity change
    - Object in mid-air (no downward collision in range) -> decrement downward velocity until grav max
- Collision
    - Object has collision in direction of velocity -> velocity in that direction zeroed
    - Object has no collision in direction of velocity -> object continues to move in that direction

Situations and outcomes:
- Stationary in mid-air - object begins to fall straight down
- Stationary on surface - object doesn't move
- Moving horizontally on surface - object continues to move until it collides with something
- Moving horizontally off a cliff - object moves horizontally until it has no downward collision, then downward force is added each update. 
- Jumping from stationary - object has upward force added to it once, but gravity will apply each loop and the upward force will decrease until it becomes stationary and then moves down
- Jumping while moving - upward force added to existing force. 

Collision direction is a tricky problem, i.e. "movement in which direction caused us to collide with this thing?" 
- If we're moving along one axis and a collision occurs, we know the direction that caused the collision (see below for edge case)
    - The collision algorithm works by moving the object then testing; collisions only occur because we moved into something
    - We can't be moving downwards and cause a horizontal collision
- If we're moving on two axes and collision occurs, there are three cases:
    - vertical movement caused the collision irrespective of horizontal; vertical movement is halted
    - horizontal movement caused the collision irrespective of vertical; horizontal movement is halted
    - movement on both axes was required for the collision; all movement is halted
- For two axis movement resulting in collisions, we can:
    - invert the move, then retry as two separate single-axis moves. This could result in side effects.
- Alternatively, we can do _every_ move as a single axis move, and just do the two axes separately. (this is probably easiest)

### Plan
(assume the core game loop will call `PhysicsManager::update()` once per loop)

#### pseudocode
General:
```
typedef Magnitude PositionUnit; // integer type

struct Direction : Point {
    int x, /* both x and y can only be 
    int y     -1, 0, or 1, 8 possible states */
}

struct Force {
    Point direction,
    Magnitude magnitude
}
```

For `physicsComponent`: 
```
// adds force to object.force
component::applyForce(force);

// object.force getter
component::getForce();

// object.force setter
component::setForce(force);

// set object's force to stationary
component::clearForce();

// returns true/false if force is nonzero
component::isMoving()

// Try movement along each axis separately; if it results in a collision, 
// undo the movement and set force in that direction to 0.
attemptMove(){
    this->moveX(); // moves force.magnitude units in force.direction.x
    if isColliding(){
        this->moveXReverse(); // moves force.magnitude units in -(force.direction.x)
        this->force->direction->x = 0
    }

    this->moveY(); // moves force.magnitude units in force.direction.x
    if isColliding(){
        this->moveYReverse(); // moves force.magnitude units in -(force.direction.x)
        if this->force->direction->y > 0 {
            this->canJump = true; // this is a private element that we will make accessible via a getter
        }
        this->force->direction->y = 0
    }
}
```

For `physicsManager`:
```
PhysicsManager::update(){
    for each component {
        applyGravity(component)
        if component.isMoving(){
            component.attemptMove()
        }
    }
}

PhysicsManager::ApplyGravity(object){
    if (object.force.y < GRAV_MAX) {
        object.force += GRAV_INCREMENT // "down" has a higher y value 
    }
}
```

For `Character`:
```
Character::move(action){
    switch(action){
        case MoveUp:
            this->jump()
            break;
        case StopMoveLeft:
            break:
        case MoveLeft:
            break;
            ...
    }
}

Character::jump(){
    if (physicsComp->canJump || jumpCount < maximum){
        apply jumping force
        if not physicsComp->canJump, jumpcount++
    }

}
```

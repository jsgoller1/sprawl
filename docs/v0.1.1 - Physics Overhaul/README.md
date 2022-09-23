# Physics overhaul

The current way of managing gravity completely sucks and results in janky-ass behavior. We need better collisions, velocities, and gravity.

## Thoughts
### Background physics concepts
- velocity is a "vector quantity", with "speed" and "direction"
    - Speed is a scalar; units are non-directional magnitude over time, i.e. units per second
    - Direction is the vector component, no units. 
    - Velocity is definied with derivatives; can be thought of as "change in position with respect to time.
    - Units: "directional distance per time", e.g. "three units left per second"
- acceleration refers to change in the direction or speed of a velocity. 
    - acceleration is also defined with derivatives; can be thought of as "change in velocity with respect to time"
    - units: "directional distance per time"^2, i.e. meters per second squared. 
- momentum is the product of mass and velocity
    - units: mass * directional distance / time, e.g. "kg * m/s". 
- force is 
- If something is in motion with no acceleration, this is due to the sum of forces applied to it cancelling each other out; per newton's second law, it stays in motion until another force acts on it.
    - A car travelling at 100mph with no acceleration has a sum of forces acting on it: the engine is applying force enough to overcome the gravity/friction, air resistance, etc. If the driver takes their foot off the gas, the engine applies less force, so the net force is no longer 0 and the car decelerates. 

So, concretely:
- force = mass * acceleration
- acceleration = force / mass
- new position = initial position + (velocity * time)
    - only works for objects that aren't accelerating
    - if an object starts at 0,0 and has constant velocity of (5 units per second in direction 1,1) over 4 seconds, then it ends at 20,20

### Approach to implementation
- Every object should have mass, velocity, acceleration, and drag/dampening 
    - drag/dampening depends on what surface the object is on (mid-air, ground, water, etc). For now, we will just have "mid air drag" and "regular drag". 
    - Each object has its current drag, which can be obtained from the PhysicsManager
    - We aren't implementing friction; just a global "here's how much you slow down each frame if you're in mid-air or not"
- We don't attempt to move objects as part of handling user input, reconciling collisions, etc. We just apply forces to them.
    - We apply gravity (also a force) each frame
- When we "handle physics", we "integrate"; this means we use apply all forces to an object, use them with the object's mass and acceleration to determine its velocity, which determines its positional movement.
- We then attempt the move and check for collisions. 
    - If one occurs, the object applies a force to what it collides with, and has an opposing force applied back depending on the direction of the collision

### Issue: handling player movement
- Presently, we just set the player's velocity and update their position based on it each frame. We can't do this with our new force-based movement system.
- The player expects their character to move in the direction of their button press as long as they hold it down, and stop once they  release it. Small acceleration / deacceleration is acceptable. 
- In order to achieve any velocity, a character must have sufficient force applied to it so it can accelerate.
    - If we use force to achieve player movement, the player will stay in motion until another force stops them. 
    - If we implement stopping as "releasing the key applies backward force to stop movement," it will result in bizarre behavior if other forces are applied while the character is in motion (e.g. running into a wall.)
- One solution is to apply a drag force to any object in motion.
    F_drag = -a * velocity; a is a drag constant. 
- To stay in motion, a character must have equal and opposite force to drag force added to it. 
- The dumbest/easiest way to do this would be have an initial "impulse jolt" that results in the character accelerating to their maximum velocity, then as long
as the movement key is held down, just adding a drag-counteracting force each time drag is added. 
- cyclone implements drag as a modifier to velocity. While this technically works, it leads to a painful calculation of "how much force do we add to balance out drag". If we apply drag as a force before calculating the new velocity, we can sidestep this entirely. 
- Player movement is handled as follows:
    - A player has a maximum movement speed, and we don't want to exceed it
    - When the player presses a button to move, we add force to the character.
        - Each frame, the amount of force we add might change, depening on their current speed. 
            - If their speed is not at max, we add up to a certain amount of force. 
                - e.g. suppose a character got hit by a truck and is moving backwards. if the player tries to move them forward, that will slow their backward movement, but not immediately halt it
            - If their speed is already max, we only add enough force to cancel drag.

### Issue: collision testing and forces
Collisions are "directional"; if movement occurs in the x and y direction but an x-direction collision happens, only the x velocity needs to be zeroed. So
if we do a two-axis movement and a collision occurs, we need to be able to determine which direction caused the collision. 

#### Collision for single direction movement
Trivial, we know exactly which direction the collision occurred in.

#### Collision for two direction movement
E.g. up and to the right. We can perform all movements as single-direction by breaking up their respective moves along each axis and testing them separately.
- An edge case occurs here if only the diagonal movement would cause a collision. Not sure how I want to handle this yet.
- Collisions can't occur in a direction we're not moving; when we move-and-test, our move is what causes a collision
    - Separately, something could collide with us, e.g. while we fall we are hit by a bullet. However, this won't happen concurrently; the bullet would collide with us, apply its force, and then be moved back to its original state until its next move is calculated
    
## Plan
### New physics and position types
A whole bunch of `cyclone-physics` code can be adapted for 2D vector math

Single dimension:
- Magnitude (int)
- Mass (int); can never be 0. 
- Dampening (int)

Two dimensions:
- Vect2D: has int x and int y
- Direction: a Vect2D whose x and y values are constrained to -1, 0, or 1. 
    - We will define all cardinal directions as constants at compile time
- We will want to define vector addition, scaling, and scale-then-add

Composition:
- Force: has Direction and Magnitude
- Velocity: has Direction and Magnitude
- Acceleration: has Direction and Magnitude

### New attributes/methods
PhysicsComp:
- attrs
    - Mass, Velocity, and Acceleration
    - Movable (bool): can forces applied to this cause movement?
- Methods
    - getters/setters for each attr
    - void applyForce(Force): updates acceleration of an object via newton's laws. 
    - bool isMoving(): returns whether velocity is 0 or not
    - moveX(), moveY(), moveReverseX(), moveReverseY(): 

PhysicsManager:
- AirDampening and SurfaceDampening (eventually we may want more / different ones)

### Other details
- I want to stick with ints if possible, but we might not be able to due to calculating net force on an object (which will require inverse mass)
- Horizontal movement in mid-air is allowed; pretty common for platformers
- Double jumping is allowed (or even multi-jumping, could be upgradable)

### Test scenarios
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

## Pseudocode
(assume the core game loop will call `PhysicsManager::update()` once per loop)

For `physicsComponent`: 
```
// adapted from https://github.com/idmillington/cyclone-physics/blob/master/src/particle.cpp
integrate(time duration)
{
    if (mass <= 0 or duration <= 0) {
        return;
    }
    // Attempt movement based on velocity based on
    // object's velocity over the duration;
    // we will scale the velocity vector based on time
    // and add that to position, taking collisions into account
    attemptMove(duration)

    // Update our acceleration from forces accumulated since last 
    // integration, then use that to update our velocity
    this->acceleration->addScaledVector(this->forceAccum, 1/this->mass);
    this->velocity.addScaledVector(this->acceleration, duration);

    // Impose drag.
    this->velocity *= real_pow(this->damping, duration);

    this->forces->clear();
}

// Try movement along each axis separately; if it results in a collision, 
// undo the movement and set force in that direction to 0.
attemptMove(){
    this->moveX(); // moves force.magnitude units in force.direction.x
    if isColliding(){
        this->moveXReverse(); // moves force.magnitude units in -(force.direction.x)
        // We should attempt to move as close to the object as possible; maybe add a collisionDistance()
        // that knows the closest we can get to its bounding box?
        apply equal to opposite of x direction
    }

    this->moveY(); // moves force.magnitude units in force.direction.x
    if isColliding(){
        this->moveYReverse(); // moves force.magnitude units in -(force.direction.x)
        if this->force->direction->y > 0 {
            this->canJump = true; // this is a private element that we will make accessible via a getter
        }
        apply equal to opposite of y direction
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
    if the object's downward acceleration isn't greater than max:
        apply gravitational force
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
            - apply dampening
        case MoveLeft:
            - disable dampening 
            - apply force in left direction
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

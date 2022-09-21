# Tech spec
- Core game loop to drive execution
- World owns Zones; only one Zone is active at a time
- Zones contain GameObjects
- Characters, Bullets, and Platforms are GameObjects
- GameObjects need to do physics, so they have a PhysicsComponent
- GameObjects implement a position interface, but maybe will just have a PositionManager
- Characters need AI, so they have an AIComponent
- Each zone has an AIManager and PhysicsManager
- AIManager and PhysicManager manage GameObjects by respectively tracking their
  PhysicsComponents and AIComponents
    - PhysicsManager knows how to determine collisions, so PhysicsComponents
      have to ask it if they're colliding 
    - AIManager will know about stuff like waypoints or visibility, so AIComponents
      will ask it how to do things like pathfinding or if they can detect enemies. 
- Screen knows how to draw stuff, but not what
- World knows what to draw but not how
  - World should possibly have a DisplayManager that can take a list of objects based on layers/positions/etc and determine
    which should be visible vs occluded, then tell Screen to draw them. 


## Example code
```c++
class Screen {
  // Screen manages actually drawing stuff on the screen; for now, it handles
  // any SDL functionality related to drawing the window and actually putting
  // things in it. All entities in the World _can_ be drawn, and Screen knows
  // how. However, only World knows _if_ an GameObject should be drawn; it then
  // communicates this to Screen.

  // Screen implements an MVC View.

  // TODO: Menu, UI, dialogue boxes, etc should always be drawn on top of items
  // from World; when the UI system is implemented, it will tell Screen what to
  // draw, but all of it will take precedence over World items.

 public:
  draw()

}

class World {
  // Keeps track of the interactive game world state, e.g. which
  // Characters, Zones, and GameObjects exist in the world. World knows if an GameObject
  // should be drawn, but not how to draw it (Screen knows how).

  // TODO: Menus, UI, dialogue boxes, etc should not be part of the world

  // World implements an MVC Model

 public:
  World() {
    // Set up zones
  }
  update(user_input) {
    // The current zone owns all of the currently active GameObjects
    currentZone.update()
  }

 private:
  Zone currentZone;
  Collection<Zone> zones;
  draw() {
    // Collects whatever GameObjects should be drawn
    // and gives them to the screen for drawing
  }
}

class InputManager {
  // InputManager is responsible for getting keystrokes and mouse movements, and
  // signalling to the World that elements within it should change somehow.

  // InputManager implements an MVC Controller.
}

class Zone {
  // A Zone is a location in the World containing GameObjects
  // TODO: Initially, all zones are rectangular, have the same height as the
  // window, and every part of them should be drawn on the screen. Eventually,
  // we'll want to be able to scroll around in them

 public:
  update() {
    updateAI();
    updatePhysics();
  }
  Zone() {}

 private:
  AIManager aiManager;
  PhysicsManager physicsManager;
  Collection<GameObject> gameObjects;
  Background background;
  load() {
    // We'll hardcode the zone state initially. Eventually, we'll want to load
    // textures, positions, music, etc from WAD files we can design as data (and
    // perhaps emit with a level design tool).
  }

  // We only need to care about physics and AI going on in currentZone,
  // since only currentZone will have active GameObjects. Additionally, physics
  // might differ based on zone (underwater, outer space, cyberspace, etc)
  updateAI(){this->aiManager.update()} updatePhysics() {
    this->physicsManager.update()
  }
}

class GameObject {
  // GameObjects are anything interactive in the world;
  // items, characters, vehicles
 public:
  Position setPosition() Position getPosition();
  Position move();

 private:
  Position position;
  PhysicsManager physicsManager;
}

class PhysicsComponent {
  // Any GameObject can have a physics component; if it does, it registers
  // it with the global PhysicsManager.
 public:
  move();  // forward method for parent's move()
  Collection<GameObject> getCollisions();

 private:
  bool collisions_enabled;
  bool gravity_enabled;
  GameObject parentGameObject;
  BoundingBox boundingBox;
}

class AIComponent {
}

class BoundingBox {
  // BoundingBoxes manage collision detection. SDL implements several functions
  // we can use for this, but they require using SDL-specific classes that we'd
  // have to expose, so we may want to use a Strategy or Factory to allow that
  // if we're using SDL-based bounding boxes
}

class Platform : GameObject {
  // Platforms are gravity-disabled surfaces with colliders; examples include
  // walls, floors, cielings, ground, etc.
}

class Character : GameObject {
  // Self explanatory: parent class for player, npcs, enemies, etc
 public:
  shoot();

 private:
  AIComponent aiComponent;
}

class Bullet : GameObject {
  // Represents in-game projectiles
}

class PhysicsManager {
  // Keeps track of registered PhyiscsComponents and
  // knows how to apply physics to them
 public:
  applyGravity() {
    //
  }

 private:
  Collection<PhysicsComponent> managed;

}

class AIManager {
  // Keeps track of registered AIComponents and
  // knows how to tell them what to do next.
 public:
  applyGravity() {
    //
  }

 private:
  Collection<PhysicsComponent> managed;

}

main() {
  screen = Screen();
  world = World();
  inputManager = IntputManager() InputType userInput;

  while (userInput != quit) {
    startTime =
        getCurrentTime() userInput =
            inputManager
                .processInput()
            // TODO:
            // uiSystem = UISystem() // ui can either pause the game (settings
            // menu) or not (in-game menu for "doing something" mid-game);
            // pausing would mean just skipping world.update()
            world.update(userInput) screen.draw(world)
                sleep(startTime + MS_PER_FRAME - getCurrentTime())
  }
}
```

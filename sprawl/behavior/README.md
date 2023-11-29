# Behavior component subsystem
The behavior component subsystem in Sprawl is extremely complicated and hard to understand. I came up with this idea
after a day or so of back-and-forth with GPT (and I am _definitely_ not skilled enough at C++ to figure this out on my own).

## Intro
Sprawl has two major design goals for user experience:
-  **Familiar feel to Unity**: the developer attaches "custom behavior" components to game objects (in Unity, these are C# Script Components that are added to GameObjects;
   in Sprawl, they are BehaviorComponents that are added to Actors), and the game is driven by these scripts recieving events like `OnLoop()` or `OnDestroy()` (which the programmer implements).
- The developer does not have to write a single line of code that is necessary for Sprawl but does nothing for their game. 

At the time of writing this, we had some difficult constraints:
- **Adding a scripting language is out of scope**: we instead expect the developer to write C++ which they then compile 
  against the engine (the engine is pretty small and the Makefile system is pretty fast, so this is viable - the whole 
  thing compiles from scratch in under 5 seconds). 
- **Building an interactive UI is out of scope**: As a crappy stopgap, we instead have developers write a JSON file describing what exists in their game world, 
  which Sprawl then uses to populate scenes when it starts up. (once we have a UI, we can serialize it to a binary and get rid of this whole mess).

In Unity, programmers can have one ScriptComponent object that implements `OnLoop()` completely differently than another - I don't know how they do this,
since both are subclasses of `MonoBehavior`, but I'm assuming it has something to do with reflection facilities in C# that we don't have. So instead,
we expect the developer to subclass `BehaviorComponent` and override the event handler functions whenever they want custom behaviors. Here's an example of
what that might look like:
```c++
#include "BehaviorComponent.hh"

// Developers will name their own components like this one
class SwordBehavior : public BehaviorComponent {
 public:
  BINDABLE(int, durability);
  BINDABLE(int, damagePerSecond);

  // These event handlers are implemented as nonpure virtual functions in
  // BehaviorComponent. Developers can override any of them they need. 
  void onInputEvent(time_ms duration) override {
    if (this->getInputManager()->isKeyPressed(SDL_SCANCODE_SPACE)) {
      LOG_INFO("Swinging sword");
    } else if (this->getInputManager()->isKeyPressed(SDL_SCANCODE_LSHIFT)) {
      LOG_INFO("Blocking with sword");
    }
  }

  void onCollisionEnter(const Collision& collision) override {
    LOG_INFO("Sword collided with {}", collision.other->toString());
    std::shared_ptr<Actor> other = collision.other;

    // Developers will likely want to be able to get components from actors
    // that they created as below, so we need to support this.
    other.getComponent<HealthComponent>()->damage(10);
  }

  // Developers are also free to add their own functions like this,
  // but unless they implement them in their handler functions, we
  // can't and won't do anything with them in the engine.
  void castSpell() { LOG_INFO("Casting spell"); }

  void onDestroy() override {
    LOG_INFO("Sword destroyed; placing a curse on anyone who is nearby!");
    this->castSpell();
  }
};

// Sprawl provides a macro like this that we require
// developers to use to register their components with the engine,
// but they don't need to know anything about it other than that they
// must use it (we will tell them this in docs and raise errors directing them to
// do so if they don't). 
REGISTER_COMPONENT(SwordBehavior);
```

The developer would then specify something in the WAD file like this:
```json
{
  ...
  "actors": [
    {
      "name": "bob the knight",
      "components": [
        {
          "type": "SwordBehavior",
          "attributes": {
            "durability": 100,
            "damagePerSecond": 15
          }
        }
      ]
    }
  ]
}
```

Then when they start Sprawl with their WAD file, Sprawl creates an Actor with name "bob the knight", which has a 
SwordBehavior component with the two listed attributes. 

## The problem: how do we build things we don't know about?
Our setup has a nasty problem: we want developers to subclass BehaviorComponent with custom behaviors and attach those subclasses to their Actors. 
However, we can't know what types they will derive from BehaviorComponent. So, how do we actually construct the Actors?

## Solution
WIP (need to make sure this works before documenting implementation details further)

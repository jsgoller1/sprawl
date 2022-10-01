# Entity component system

## Background
Sprawl was intended to be an entity-component system (I just didn't know this was what it was called). This involves the following classes:
- **Entities**: these objects "exist" in the game world and can do things, but they "don't know how". Example: `GameObject`, `Background`
- **Components**: these objects know "how to do things", and are owned by `Entities`. Example: `PhysicsComponent` knows about mass, velocity, gravity, and how to calculate acceleration from net force. 
- **Managers**: these objects own collections of components given to them by `Entities`, and how to handle interactions between them. Example: `PhysicsManager` knows how to determine which objects are colliding, but it has to ask a `PhysicsComponent` (e.g. `PhysicsComponent` may have a `bool isColliding(componentA, componentB))` method, which `PhysicsManager` then calls against any other components a particular physics component might collide with). 

The rule of thumb is: if an operation can be done completely with the information owned by a single component, then the component should be responsible for doing it. Otherwise (i.e. more information is required that one component has access to), the manager should do it. Examples:
- A single PhysicsComponent can calculate its own velocity, acceleration, etc. from its net force and mass, so it should own `calculateVelocity()` and similar functions. 
- Determining which objects need to check collisions (e.g. if we are using space partitioning) requries knowledge of several `PhysicsComponents`, so `PhysicsManager` should do it. 
- Determining if a collision occurred requires knowledge of two `PhysicsComponents`; a single component can calculate if it's colliding with a single other component by knowing the other component's bounding box. This should probably be done by `PhysicsComponent`, but may require input from `PhysicsManager`. 

## The problem
We're going to have many systems that are implemented via Managers that interact with Components owned by GameObjects: Physics, Animation, Audio, AI, Combat, etc. Thus we want reusable logic for the following:
- Entity
    - Identity (unique, immutable information identifying an entity)
- Manager
    - Registering and unregistering components
    - Checking if a component is managed
- Component
    - Getting a reference to the manager
    - Getting a reference to the owner of the component 

## Details 
We could go about this implementation a few ways

### Inheiritance, but no smart pointers
We could try having abstract base classes `Entity`, `Manager`, and `Component`. 
```c++
class Manager { 
    private:
        shared_ptr<set<shared_ptr<Component>>> ownedComponents;
 }

class PhysicsManager : public Manager { ... };
 
class Component {
    public:
        virtual Manager* getManager() const = 0;
    private: 
        Manager* manager; 
};
 
class PhysicsComponent : public Component {
    public:
        PhysicsManager* getManager() const override { ... };
};
```
This works fine at first glance; AnimationManager is called a [covariant return type](https://en.wikipedia.org/wiki/Covariant_return_type); "covariant" here means "`AnimationManager` is a narrower/more specific version of `Manager`". This is allowed so that we can effortlessly replace instances of `Manager` with derived types, per the [Liskov substitution rule](https://en.wikipedia.org/wiki/Liskov_substitution_principle). However, we have two problems:
- We can't use smart pointers. If we change `Manager*` and `AnimationManager*` to `shared_ptr<Manager>` and `shared_ptr<AnimationManager>`, compilation will fail because unlike the raw pointers to covariant return types, smart pointers to covariant return types are not allowed. 
- All managers own a collection of a specific type of component. `PhysicsManager` will need to have something like `set<shared_ptr<PhysicsComponent>>` or `vector<shared_ptr<PhysicsComponent>>`. 

### Inheiritance with smart pointers via CRTP
We might be able to get around the limitations with smart pointers by utilizing the "curiously recurring template pattern". This involves creating the parent object as a template class, and the derived object as a self-referential use of the template. We then put the important functionality into the parent object, which downcasts itself at runtime:






### Scratch
#### Smart pointers to covariant return types
Suppose we have the following situation:
- We have abstract base classes `Manager` and `Component` as part of our entity-component architecture so that new components can reuse code for interacting with a respective `Manager` and vice versa. 
- New components and managers respectively inheirit from `Component` and `Manager`; `AnimationComponent` will be managed by `AnimationManager`. 
- We need to support a `Component::getManager()` that returns a pointer to whatever manager manages that component.
- We want to use smart pointers as aggressively as possible. 

So in order to ensure each component derived from `Component` inheirits an interface for interacting with a `Manager`, we might do the following:
```c++
class Manager { ... }
class AnimationManager : public Manager { ... };
 
class Component {
    virtual Manager* getManager() const = 0;
};
 
class AnimationComponent : public Component {
    AnimationManager* getManager() const override { ... };
};
```
This works fine; AnimationManager is called a [covariant return type](https://en.wikipedia.org/wiki/Covariant_return_type); "covariant" here means "`AnimationManager` is a narrower/more specific version of `Manager`". This is allowed so that we can effortlessly replace instances of `Manager` with derived types, per the [Liskov substitution rule](https://en.wikipedia.org/wiki/Liskov_substitution_principle). However, if we change `Manager*` and `AnimationManager*` to `shared_ptr<Manager>` and `shared_ptr<AnimationManager>`, compilation will fail because unlike the raw pointers to covariant return types, smart pointers to covariant return types are not allowed. To get around this problem, we do the following: [WIP]

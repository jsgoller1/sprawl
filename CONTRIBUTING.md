# Contributing guidelines
## Coding conventions
### Mandatory const correctness
Everything should be `const` everywhere until proven otherwise. Start by making every argument, attribute, pointer, function, etc `const` and then remove `const` only when mutation is necessary.

### Use full names and types. 
- `PhysicsManager` is better than `PhysMgr`
- `shared_ptr<PhysicsManager>` is better than `typedef shared_ptr<PhysicsManager> PhysicsManagerSPtr`.

### Use components 
Neon Rain is modeled after an entity-component system, so consider creating a new component and composing it into GameObject when adding new functionality. Avoid bloating GameObject or using inheiritance. 

### Smart pointers vs references
- Use smart pointers over const references when possible. 
- Use smart pointers everywhere a pointer is used. Do not use raw pointers. 
- If you have to use raw pointers to interface with another API (i.e. SDL), do it as close to the API calls as you can, and consider creating a class that will automatically manage the raw pointer, then wrapping that in a smart pointer. 
    - This is especially important for SDL; I once caused a 1 GB / sec memory leak by not cleaning up textures correctly, and my machine hung until the Linux OOM killer killed the program. 
- Do not use smart pointers as arguments for operator loading - use const references instead. Overloaded operators should work only on const references to objects. 
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
This works fine; AnimationManager is called a [covariant return type](https://en.wikipedia.org/wiki/Covariant_return_type); "covariant" here means "`AnimationManager` is a narrower/more specific version of `Manager`". This is allowed so that we can effortlessly replace instances of `Manager` with derived types, per the [Liskov substitution rule](https://en.wikipedia.org/wiki/Liskov_substitution_principle).

 However, if we change `Manager*` and `AnimationManager*` to `shared_ptr<Manager>` and `shared_ptr<AnimationManager>`, compilation will fail because unlike the raw pointers to covariant return types, smart pointers to covariant return types are not allowed. To get around this problem, we do the following: [WIP]



### Use dependency injection and RAII
- All constructors should follow RAII; a constructor should handle the creation/initialization of all owned objects and attributes
- All objects should have a constructor that supports dependency injection via optional parameters. Prefer dep injection with default parameters resulting in default objects over passing parameters for the construction of owned objects. 

### Try not to put code in headers
The general rule is "header files (`.hh`) describe what something is and what it can do, source files (`.cc`) describe how it does it". Code should usually go into `.cc` files, but some exceptions are acceptable (either for convenience / concision, or because it breaks the general rule):
- Attribute getters and setters that are a single line return or assignment; these should not go in source files unless they're longer than a single line. 
- Static methods that fundamentally change the nature of a class, such as a static `instance()` method for a Singleton class (e.g. `EntityManager`).
- Static methods used in place of constants, e.g. `Direction::Up()`. 

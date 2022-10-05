# CONTRIBUTING

## Conventions
### Use full names and types. 
- `PhysicsManager` is better than `PhysMgr`
- `shared_ptr<PhysicsManager>` is better than `typedef shared_ptr<PhysicsManager> PhysicsManagerSPtr`.

### Use components 
Neon Rain is modeled after an entity-component system, so consider creating a new component and composing it into GameObject when adding new functionality. Avoid bloating GameObject or using inheiritance. 

### Smart pointers vs references
- Use smart pointers everywhere a pointer is used. Do not use raw pointers. 
- Use smart pointers over const references when possible. 
- If you have to use raw pointers to interface with another API (i.e. SDL), do it as close to the API calls as you can, and consider creating a class that will automatically manage the raw pointer, then wrapping that in a smart pointer. 
    - This is especially important for SDL; I once caused a 1 GB / sec memory leak by not cleaning up textures correctly, and my machine hung until the Linux OOM killer killed the program. 
- Do not use smart pointers as arguments for operator loading - use const references instead. Overloaded operators should work only on const references to objects. 

### Mandatory const correctness
Everything should be `const` everywhere until proven otherwise. Start by making every argument, attribute, pointer, function, etc `const` and then remove `const` only when mutation is necessary.

### Class definitions
The general rule is "header files (`.hh`) describe what something is and what it can do, source files (`.cc`) describe how it does it". Code should usually go into `.cc` files, but some exceptions are acceptable (either for convenience / concision, or because it breaks the general rule).
 There should be only one definition per header file and an associated `.cc` file; multiple classes can go in the same header if one is very small and intimately related to the other. All data attributes (including references to owned objects) go in the `private` section, and should have accompanying accessors (getter/setter methods). 
 
 All method definitions belong in `.cc` files, except:
- Constructors using attribute-setting syntax 
- One-liner accessors for attributes
- Methods calling a different version of an overloaded method
- Static methods that fundamentally change the nature of a class, such as a static `instance()` method for a Singleton class (e.g. `EntityManager`).
- Static methods used in place of constants, e.g. `Direction::Up()`. 

Class sections should be defined in this order:
- Public/Protected:
    - Constructors
    - Accessors for owned components
    - Forwarding methods to owned components
    - Accessors for unique attributes
    - Unique methods
- Private:
    - Hidden constructors
    - Owned component attributes
    - Unique attributes
    - Unique private methods

Example:
```c++
// in Foo.hh

class Foo {
    public:
        // ctors / dtors first
        // simple constructors using attribute-setting syntax,
        // declare and define here
        Foo(const int attr1) : attr1(attr1) {} 
        // complicated, multiline constructor; declare here, define in .cc file
        Foo(const string& complicatedConstructorArg);

        // Accessors for owned components; declare and define here
        void setBar(const shared_ptr<Bar> bar) { this->bar = bar; }
        getBar() const { return this->bar; }
        ...

        // Fowarding methods to owned components; declare and define here
        void barBehavior() { this->bar->barBehavior; } 

        // Accessors for unique attributes; declare and define here
        void setAttr1(const int attr1) { this->attr1 = attr1; }
        int getAttr1() const { return this->attr1; }

        // Unique methods; declare here, define in .cc file
        float uniquePublicMethod() const;

    private:
        // Hidden constructor
        Foo(const float someIllegalValue);

        // Owned components
        shared_ptr<Bar> bar;
        ...

        // Unique attributes
        int attr1;
        ...

        // Unique methods; declare here, define in .cc file
        int uniquePrivateMethod();
};
```

### Constructors should only allow RAII-compliant dependency injection
- The only parameters constructors should accept are pointers/references to owned objects (or nullptr) and raw values for the object's own attributes. Do not pass parameters to constructors of owned objects:
```c++

class OwnedThing {
    public:
        OwnedThing(int something);
};

class DoThis {
    public:
        DoThis(const int attribute, const shared_ptr<OwnedThing> thing) : attribute(attribute), thing(thing) {}
    private:
        int attribute;
        shared_ptr<OwnedThing> thing;
};

class DontDoThis {
    public:
        DontDoThis(const int attribute, const int x); // then in DontDoThis.cc you'd have construct an OwnedThing with x
    private:
        int attribute;
        shared_ptr<OwnedThing> thing;
}

```
- All constructors should provide default values for attributes that are not required for successful construction. 
- All ctors/dtors should follow RAII; a constructor should handle the creation/initialization of all owned objects and attributes, and likewise with dtors handling cleanup. 
- If numerous valid ways to construct an object exist, define them as needed and have them call an `init()` method that does not support default arguments. 

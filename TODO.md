# TODO
## Set up compilation via Bazel
- Integrate gtest with Bazel (easy, see Omerta)
- Integrate SDL2 with Bazel (hard)
- Tried using system install via apt-get, didn't know how to include all headers, .a, and .so files
    - Can likely get this working with more time
- Tried building SDL2 source in local directory and including it as external repo
- Tried using https://github.com/bazelregistry/sdl2, didn't build
- If system install doesn't work well, might be a good idea to copy repo and bazel-ify it for inclusion via http archive like gtest

## names for smart pointers
- don't like "SPtr" on variables after all; should be an assumption that every reference to an object is via a smart pointer (and can be checked via cross-referencing)

## Set up forwarding methods for composition classes
Some cases won't work well (i.e. positionManager with several different ways to set position).
- Do we want to have "Manager who gets components from objects and talks to objects through them", e.g. physics manager interacting with physics components, or "manager manages objects via forwarding methods", i.e. GameObject forwards all methods to PhysicsComponent
    - I think latter case will turn into a god class, but so will the former; physicsComponent will need to update position, so it'll either have to do that through its parent game object or get a reference to the PositionComponent
    - Unity looks like it doesn't do aggressive forwarding with owned components: https://docs.unity3d.com/ScriptReference/GameObject.html

## Shared from this bug
Why did using `class PhysicsMgr : public enable_shared_from_this` fix the bug that was happening when `public` wasn't used? 

## Points and vectors
I should probably create a 2D vector class that has magnitude and direction and 
can be used for movement. Can maintain Point as the underlying direction component,
and use it for location. 

#include "Platform.hh"

Platform::Platform(const shared_ptr<Vect2D> center,
                   const GameObjectNameSPtr name,
                   const shared_ptr<PhysicsComp> physicsComp,
                   const FilePathSPtr texturePath,
                   const DrawingCompSPtr drawingComp)
    : GameObject(center, name, physicsComp, texturePath, drawingComp) {}

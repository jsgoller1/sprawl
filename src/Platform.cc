#include "Platform.hh"

Platform::Platform(const PointSPtr center, const GameObjectNameSPtr name,
                   const shared_ptr<PhysicsComp> physicsComp,
                   const FilePathSPtr texturePath,
                   const DrawingCompSPtr drawingComp)
    : GameObject(center, name, physicsComp, texturePath, drawingComp) {}

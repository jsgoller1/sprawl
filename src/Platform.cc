#include "Platform.hh"

Platform::Platform(const PointSPtr center, const GameObjectNameSPtr name,
                   const PhysicsCompSPtr physicsComp,
                   const FilePathSPtr texturePath,
                   const DrawingCompSPtr drawingComp)
    : GameObject(center, name, physicsComp, texturePath, drawingComp) {}

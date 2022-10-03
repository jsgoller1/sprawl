#pragma once

#include "GameObject.hh"
#include "PhysicsComponent.hh"

class Platform : public GameObject {
  // Platforms are gravity-disabled surfaces with colliders; examples include
  // walls, floors, cielings, ground, etc.
 public:
  Platform(const shared_ptr<Vect2D> center,
           const GameObjectNameSPtr name = nullptr,
           const shared_ptr<PhysicsComponent> physicsComp = nullptr,
           const FilePathSPtr texturePath = nullptr,
           const DrawingCompSPtr drawingComp = nullptr);

 private:
  shared_ptr<PhysicsComponent> physicsComp;
  PhysicsComponent* getRawPhysicsComponent() override {
    return this->physicsComp.get();
  }
};

typedef shared_ptr<Platform> PlatformSPtr;

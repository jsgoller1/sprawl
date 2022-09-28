#pragma once
#include <gtest/gtest.h>

#include "GameObject.hh"

class TestGameObject : public GameObject {
 public:
  TestGameObject(const PointSPtr center, const GameObjectNameSPtr name,
                 const shared_ptr<PhysicsComp> physicsComp = nullptr,
                 const FilePathSPtr texturePath = nullptr,
                 const DrawingCompSPtr drawingComp = nullptr)
      : GameObject(center, name, physicsComp, texturePath, drawingComp){};
};

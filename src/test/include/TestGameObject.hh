#pragma once
#include <gtest/gtest.h>

#include "GameObject.hh"

class TestGameObject : public GameObject {
 public:
  TestGameObject(const shared_ptr<Point> center,
                 const shared_ptr<GameObjectID> name,
                 const shared_ptr<PhysicsComponent> physicsComponent = nullptr,
                 const shared_ptr<FilePath> texturePath = nullptr,
                 const shared_ptr<DrawingComponent> drawingComponent = nullptr)
      : GameObject(center, name, physicsComponent, texturePath,
                   drawingComponent){};
};

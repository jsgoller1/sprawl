#pragma once
#include <gtest/gtest.h>

#include "GameObject.hh"

class TestGameObject : public GameObject {
 public:
  TestGameObject(const std::shared_ptr<Vect2D> center, const std::shared_ptr<Identity> name,
                 const std::shared_ptr<PhysicsComponent> physicsComponent = nullptr,
                 const std::shared_ptr<FilePath> texturePath = nullptr,
                 const std::shared_ptr<GraphicsComponent2D> graphicsComponent2D = nullptr)
      : GameObject(center, name, physicsComponent, texturePath, graphicsComponent2D){};
};

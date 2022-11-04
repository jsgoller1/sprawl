#include "TestGameObject.hh"

TEST(GameObject, construction) {
  // This is a crappy test; just using it
  // as a proof of concept for gtest working
  shared_ptr<Vect2D> center = shared_ptr<Vect2D>(new Vect2D());
  shared_ptr<Identity> name = shared_ptr<Identity>(new GameObjectID());
  GameObject obj = TestGameObject(center, name);
  EXPECT_NE(obj.getDrawingComponent(), nullptr);
  EXPECT_NE(obj.getPhysicsComponent(), nullptr);
}

#include "PhysicsMgr.hh"

PhysicsMgr::PhysicsMgr() {
  this->managedComponents = shared_ptr<set<shared_ptr<PhysicsComp>>>(
      new set<shared_ptr<PhysicsComp>>());
}

bool isAboveEq(const PositionUnit y1, const PositionUnit y2) {
  // 0,0 is the top left of the screen, so
  // "above" means "lesser y value"
  return y1 < y2;
}
bool isBelowEq(const PositionUnit y1, const PositionUnit y2) {
  // 0,0 is the top left of the screen, so
  // "below" means "greater y value"
  return y1 > y2;
}
bool isLeftEq(const PositionUnit x1, const PositionUnit x2) { return x1 <= x2; }
bool isRightEq(const PositionUnit x1, const PositionUnit x2) {
  return x1 >= x2;
}

bool xFallsWithin(const PositionUnit leftBound, const PositionUnit rightBound,
                  const PositionUnit testPoint) {
  return isLeftEq(leftBound, testPoint) && isLeftEq(testPoint, rightBound);
}

bool yFallsWithin(const PositionUnit highest, const PositionUnit lowest,
                  const PositionUnit testPoint) {
  return isAboveEq(highest, testPoint) && isAboveEq(testPoint, lowest);
}

std::shared_ptr<PhysicsMgr> PhysicsMgr::getptr() {
  // TODO: This is dangerous and leads to undefined behavior if no other
  // shared pointers to this object exist; it would be best to force
  // any construction to return a shared pointer, but that might not be
  // viable. See:
  // https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
  return this->shared_from_this();
}

void PhysicsMgr::manageComponent(const shared_ptr<PhysicsComp> component) {
  if (component->getManager() != nullptr) {
    // TODO: Log a warning
    return;
  }
  component->setManager(this->getptr());
  this->managedComponents->insert(component);
}
void PhysicsMgr::unmanageComponent(const shared_ptr<PhysicsComp> component) {
  if (component->getManager() != this->getptr()) {
    // TODO: Log a warning
    return;
  }
  component->setManager(nullptr);
  this->managedComponents->erase(component);
}

void PhysicsMgr::applyGravity() {}
bool PhysicsMgr::areColliding(const shared_ptr<PhysicsComp> comp1,
                              const shared_ptr<PhysicsComp> comp2) {
  // TODO: Probably want bounding objects to know how to
  // determine collisions, not PhysicsManager. Fine for now.
  // TODO: SDL implements several functions and types we can use
  // for collision detection; this works fine for now.
  PointSPtr loc1 = comp1->getCenter();
  BoundingBoxSPtr box1 = comp1->getBoundingBox();
  PointSPtr loc2 = comp2->getCenter();
  BoundingBoxSPtr box2 = comp2->getBoundingBox();

  // 0,0 is the upper lefthand corner, see remark:
  // https://wiki.libsdl.org/SDL_SetWindowPosition
  PositionUnit comp1YHighest = loc1->y - (box1->height / 2);
  PositionUnit comp1YLowest = loc1->y + (box1->height / 2);
  PositionUnit comp1XLeftmost = loc1->x - (box1->width / 2);
  PositionUnit comp1XRightmost = loc1->x + (box1->width / 2);

  PositionUnit comp2YHighest = loc2->y - (box2->height / 2);
  PositionUnit comp2YLowest = loc2->y + (box2->height / 2);
  PositionUnit comp2XLeftmost = loc2->x - (box2->width / 2);
  PositionUnit comp2XRightmost = loc2->x + (box2->width / 2);

  bool intersectingY = false;
  // Check if comp2's highest or lowest y coordinate falls within comp1's y
  // range
  intersectingY |= yFallsWithin(comp1YHighest, comp1YLowest, comp2YHighest);
  intersectingY |= yFallsWithin(comp1YHighest, comp1YLowest, comp2YLowest);

  bool intersectingX = false;
  // Check if comp2's leftmost X coord falls with comp 1
  // (is it left of the rightmost and right of the leftmost);
  // then do same thing for right
  intersectingX |=
      xFallsWithin(comp1XLeftmost, comp1XRightmost, comp2XLeftmost);
  intersectingX |=
      xFallsWithin(comp1XLeftmost, comp1XRightmost, comp2XRightmost);

  return intersectingY && intersectingX;
}

shared_ptr<vector<shared_ptr<PhysicsComp>>> PhysicsMgr::getAllColliding(
    shared_ptr<PhysicsComp> component) {
  shared_ptr<vector<shared_ptr<PhysicsComp>>> collided =
      shared_ptr<vector<shared_ptr<PhysicsComp>>>(
          new vector<shared_ptr<PhysicsComp>>());
  for (shared_ptr<PhysicsComp> other : *(this->managedComponents)) {
    if (other != component && this->areColliding(component, other)) {
      collided->push_back(other);
    }
  }
  return collided;
}

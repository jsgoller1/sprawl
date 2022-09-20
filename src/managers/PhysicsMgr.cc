#include "PhysicsMgr.hh"

PhysicsMgr::PhysicsMgr() {
  this->managedComponents = shared_ptr<set<shared_ptr<PhysicsComp>>>(
      new set<shared_ptr<PhysicsComp>>());
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

  PositionUnit comp1YMin = loc1->y - box1->height;
  PositionUnit comp1YMax = loc1->y + box1->height;
  PositionUnit comp1XMin = loc1->x - box1->width;
  PositionUnit comp1XMax = loc1->x + box1->width;

  PositionUnit comp2YMin = loc2->y - box2->height;
  PositionUnit comp2YMax = loc2->y + box2->height;
  PositionUnit comp2XMin = loc2->x - box2->width;
  PositionUnit comp2XMax = loc2->x + box2->width;

  bool intersectingY = false;
  intersectingY |= ((comp1YMin <= comp2YMin) && (comp2YMin <= comp1YMax));
  intersectingY |= ((comp1YMin <= comp2YMax) && (comp2YMax <= comp1YMax));

  bool intersectingX = false;
  intersectingX |= ((comp1XMin <= comp2XMin) && (comp2XMin <= comp1XMax));
  intersectingX |= ((comp1XMin <= comp2XMax) && (comp2XMax <= comp1XMax));

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

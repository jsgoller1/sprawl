#include "PhysicsMgr.hh"

bool areLinesIntersecting(const PositionUnit low1, const PositionUnit hi1,
                          const PositionUnit low2, const PositionUnit hi2) {
  /*
   To do 2D collision testing, we need to do two separate 1D line intersection
   tests; if both intersect, a 2D collision occurs.
   For two straight lines A and B (each with start and end points l and r,
   though this works for vertical lines too), we have four cases to check:
    - The right side of A intersects with B:
      B.l <= A.r <= B.r
    - The left side of A intersects with B:
      B.l <= A.l <= B.r
    - A falls completely in B:
      B.l <= A.l < A.r <= B.r
    - B falls completely within A:
      A.l <= B.l < B.r <= A.r
  */
  bool low2Intersects = ((low1 <= low2) && (low2 <= hi1));
  bool hi2Intersects = ((low1 <= hi2) && (hi2 <= hi1));
  bool containedIn1 = ((low1 <= low2) && (hi2 <= hi1));
  bool containedIn2 = ((low2 <= low1) && (hi1 <= hi2));
  return low2Intersects || hi2Intersects || containedIn1 || containedIn2;
}

bool PhysicsMgr::anyColliding(const shared_ptr<PhysicsComp> comp) {
  for (auto otherComp : *(this->managedComponents)) {
    if (comp != otherComp && this->isColliding(comp, otherComp)) {
      return true;
    }
  }
  return false;
}

bool PhysicsMgr::isColliding(const shared_ptr<PhysicsComp> comp1,
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

  // Highest and Lowest refer to positioning on the screen; numerically,
  // Lowest is greater than Highest
  return areLinesIntersecting(comp1YHighest, comp1YLowest, comp2YHighest,
                              comp2YLowest) &&
         areLinesIntersecting(comp1XLeftmost, comp1XRightmost, comp2XLeftmost,
                              comp2XRightmost);
}

shared_ptr<vector<shared_ptr<PhysicsComp>>> PhysicsMgr::getAllColliding(
    shared_ptr<PhysicsComp> component) {
  shared_ptr<vector<shared_ptr<PhysicsComp>>> collided =
      shared_ptr<vector<shared_ptr<PhysicsComp>>>(
          new vector<shared_ptr<PhysicsComp>>());
  for (shared_ptr<PhysicsComp> other : *(this->managedComponents)) {
    if (other != component && this->isColliding(component, other)) {
      collided->push_back(other);
    }
  }
  return collided;
}

void PhysicsMgr::applyGravity(shared_ptr<PhysicsComp> comp) {
  // Gravity is a somewhat different case of velocity; in addition
  // to whatever horizontal movement we have, we want to try to move downwards
  // but undo it if we can't; we shouldn't halt horizontal velocity if we fail.
  // TODO: This can still be refactored.
  if (comp->hasGravity() && comp->getVelocity()->y < 20) {
    PointSPtr newVelocity = comp->getVelocity();
    newVelocity->y = std::min(newVelocity->y + 1, 20);
    comp->move(newVelocity);
    if (this->anyColliding(comp)) {
      comp->move(
          PointSPtr(new Point{.x = -newVelocity->x, .y = -newVelocity->y}));
      newVelocity->y = 0;
    }
    comp->setVelocity(newVelocity);
  }
}
void PhysicsMgr::applyVelocity(shared_ptr<PhysicsComp> comp) {
  // Attempt to move each point according to its current velocity.
  // If it winds up colliding with something, undo the movement,
  // and set its velocity to 0.
  PointSPtr velocity = comp->getVelocity();
  comp->move(velocity);
  if (this->anyColliding(comp)) {
    // TODO: Since we don't have to do any redrawing, we can try a strategy
    // where we attempt to move half as far as we would have, then half of
    // that, etc until the movement is less than 1 pixel; this should fix the
    // "forcefield" problem.
    comp->move(PointSPtr(new Point{.x = -velocity->x, .y = -velocity->y}));
    comp->setVelocity(PointSPtr(new Point{.x = 0, .y = 0}));
  }
}
void PhysicsMgr::applyVelocityAll() {
  for (shared_ptr<PhysicsComp> comp : *(this->managedComponents)) {
    // TODO: applying gravity here is messy and should be done elsewhere;
    // this will just get it done for the initial MVP.
    this->applyGravity(comp);
    this->applyVelocity(comp);
  }
}
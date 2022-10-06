#include "Collision.hh"

void CollisionSet::add() {}
void CollisionSet::remove() {}
bool CollisionSet::contains() {}

shared_ptr<CollisionSet> CollisionSet::setwiseAnd(
    shared_ptr<CollisionSet> otherObjects) {}
shared_ptr<CollisionSet> CollisionSet::setwiseComplement(
    shared_ptr<CollisionSet> otherObjects) {}

#pragma once

#include "GameObject.hh"
#include "IAnimation.hh"
#include "IMovement.hh"

class EvilOtto : public GameObject, public ICollision, public IAnimation {};

#pragma once

#include "GameObject.hh"
#include "IAnimation.hh"
#include "ICollision.hh"
#include "IShooting.hh"

class Player : public GameObject, public ICollision, public IShooting, public IAnimation {};

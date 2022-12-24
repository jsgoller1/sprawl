#pragma once

#include "GameObject.hh"
#include "ICollision.hh"

class Wall : public GameObject, public ICollision {};

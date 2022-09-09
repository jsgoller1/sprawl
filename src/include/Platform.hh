#include "GameObject.hh"

class Platform : public GameObject {
  // Platforms are gravity-disabled surfaces with colliders; examples include
  // walls, floors, cielings, ground, etc.
};

typedef shared_ptr<Platform> PlatformPS;

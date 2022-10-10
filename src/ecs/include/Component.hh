#include "Identity.hh"

class Component {
 public:
  shared_ptr<Identity> getOwnerIdentity() const;

 private:
  shared_ptr<Identity> ownerIdentity;
};

#include "LoadableBehaviorComponent.hh"
#include "Math.hh"

class MVPComponent : public LoadableBehaviorComponent<MVPComponent> {
 public:
  MVPComponent() : LoadableBehaviorComponent<MVPComponent>() {}
  ~MVPComponent() override = default;

  BIND(real, forceAdded, MVPComponent)

  // We'll add the force in this function
  void onLoop() override;
};
REGISTER_COMPONENT(MVPComponent);

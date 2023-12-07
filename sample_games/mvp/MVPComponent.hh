#include "LoadableBehaviorComponent.hh"
#include "Math.hh"

class MVPComponent : public LoadableBehaviorComponent<MVPComponent> {
 public:
  MVPComponent() : LoadableBehaviorComponent<MVPComponent>() {}
  ~MVPComponent() override = default;

  BIND(real, xForceAdded, MVPComponent)
  // BIND(real, yForceAdded, MVPComponent)

  // We'll add the force in this function
  void onKeyDown(char key) override;
};
REGISTER_COMPONENT(MVPComponent);

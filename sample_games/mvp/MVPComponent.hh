#include "LoadableBehaviorComponent.hh"
#include "Math.hh"

class MVPComponent : public LoadableBehaviorComponent<MVPComponent> {
 public:
  MVPComponent() : LoadableBehaviorComponent<MVPComponent>() {}
  ~MVPComponent() override = default;

  BIND(real, forceAdded, MVPComponent)
  // real forceAdded;
  // static void addforceAdded_fn() {
  //   // IFI pattern: this ensures the function is called when the method is defined.
  //   auto IFILambda = [&]() {
  //     auto constructorLambda = [&](LoadableBehaviorComponent<MVPComponent>* baseObj) {
  //       // Safe downcast since we know the actual type
  //       MVPComponent* obj = static_cast<MVPComponent*>(baseObj);
  //       obj->registerBindableVariable("forceAdded", &(obj->forceAdded), typeid(real));
  //     };
  //     LoadableBehaviorComponent<MVPComponent>::ConstructorActions.push_back(constructorLambda);
  //   };
  //   IFILambda();
  // };

  // We'll add the force in this function
  void onLoop() override;
};
REGISTER_COMPONENT(MVPComponent);

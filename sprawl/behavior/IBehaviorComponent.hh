#pragma once

#include <string>
#include <typeindex>

#include "BehaviorComponentConfig.hh"
#include "BehaviorComponentFactory.hh"
#include "BindableVariableMetadata.hh"
#include "Component.hh"
#include "Logging.hh"

// forward decls
class WADLoader;

class IBehaviorComponent : public Component {
 public:
  IBehaviorComponent() : Component() {}
  virtual ~IBehaviorComponent() override;
  virtual std::string toString() const override;

  virtual void onLoop() {}

 private:
  // Unfortunately, initializeBindables has to exist here for now. It's a bit of a hack, but it's the only way to get
  // the WADLoader to be able to call it.
  friend WADLoader;
  virtual void initializeBindables(const BehaviorComponentConfig& config) = 0;
};

/*
 * Whenever you subclass BehaviorComponent, you must register it with Sprawl. This is done by calling the
 * REGISTER_COMPONENT macro in the header file of the subclass. For example:
 *
 * class CombatComponent: public BehaviorComponent { ... };
 * REGISTER_COMPONENT(CombatComponent);
 */
#define REGISTER_COMPONENT(TYPE) static bool TYPE##_isRegistered = BehaviorComponentFactory::Register<TYPE>(#TYPE);

/*
 * Optionally, if you want to have variables in your custom BehaviorComponent subclass that can be loaded
 * from the WAD, you can use the BINDABLE macro. For example:
 *
 * class CombatComponent: public BehaviorComponent {
 *  BINDABLE(int, health);
 *  BINDABLE(int, damage);
 * };
 * REGISTER_COMPONENT(CombatComponent);
 *
 * You can then proceed to use the variables in your code as you would normally.
 */
// #define INIT_VARIABLE(TYPE, VARNAME) BehaviorComponent::registerBindableVariable(#VARNAME, &VARNAME, typeid(TYPE));

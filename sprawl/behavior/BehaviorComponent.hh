#pragma once

#include <string>
#include <typeindex>

#include "BehaviorComponentConfig.hh"
#include "BehaviorComponentFactory.hh"
#include "BindableVariableMetadata.hh"
#include "Component.hh"
#include "Logging.hh"

class BehaviorComponent : public Component {
 public:
  std::string toString() const override;

 private:
  // Method to initialize bindable variables
  void initializeBindables(const BehaviorComponentConfig& config);

  // This is just a friend specifier for the REGISTER_COMPONENT macro.
  template <typename T>
  friend bool RegisterBindableVariable(const std::string varName, T* varPtr);

  static bool registerBindableVariable(const std::string varName, void* varPtr, const std::type_info& typeInfo) {
    // This method does the actual registration.
    BindableVariableMetadata data = BindableVariableMetadata(varPtr, std::type_index(typeInfo), varName);
    variableRegistry.emplace(std::pair<std::string, BindableVariableMetadata>(varName, data));
    return true;
  }

  static std::unordered_map<std::string, BindableVariableMetadata> variableRegistry;
};

/*
 * Whenever you subclass BehaviorComponent, you must register it with Sprawl. This is done by calling the
 * REGISTER_COMPONENT macro in the header file of the subclass. For example:
 *
 * class CombatComponent: public BehaviorComponent { ... };
 * REGISTER_COMPONENT(CombatComponent);
 */
#define REGISTER_COMPONENT(TYPE) static bool isRegistered = BehaviorComponentFactory::Register<TYPE>(#TYPE);

template <typename T>
bool RegisterBindableVariable(const std::string varName, T* varPtr) {
  return BehaviorComponent::registerBindableVariable(varName, varPtr, typeid(T));
}

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
#define BINDABLE(TYPE, VARNAME) \
  TYPE VARNAME;                 \
  static bool VARNAME##_registered = RegisterBindableVariable(#VARNAME, &VARNAME);

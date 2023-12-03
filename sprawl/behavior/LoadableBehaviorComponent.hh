#include "IBehaviorComponent.hh"

// Forward decl
class WADLoader;

template <typename T>
class LoadableBehaviorComponent : public IBehaviorComponent {
 protected:
  LoadableBehaviorComponent<T>() : IBehaviorComponent() { executeConstructorActions(); }

  static bool registerBindableVariable(const std::string varName, void* varPtr, const std::type_info& typeInfo) {
    // This method does the actual registration.
    BindableVariableMetadata data = BindableVariableMetadata(varPtr, std::type_index(typeInfo), varName);
    variableRegistry.emplace(std::pair<std::string, BindableVariableMetadata>(varName, data));
    return true;
  }

  static std::map<std::string, BindableVariableMetadata> variableRegistry;
  static std::vector<std::function<void(LoadableBehaviorComponent<T>*)>> ConstructorActions;

 private:
  friend WADLoader;
  void executeConstructorActions() {
    for (const auto& action : ConstructorActions) {
      action(this);
    }
  }

  void initializeBindables(const BehaviorComponentConfig& config) override {
    /*
     * This method takes a bit of explaining. See the README.md in this directory.
     */
    for (const auto& [varName, metadata] : variableRegistry) {
      if (config.hasKey(varName)) {
        if (metadata.typeIndex == typeid(int)) {
          *static_cast<int*>(metadata.varPtr) = config.getInt(varName);
        } else if (metadata.typeIndex == typeid(float)) {
          *static_cast<float*>(metadata.varPtr) = config.getFloat(varName);
        } else if (metadata.typeIndex == typeid(std::string)) {
          *static_cast<std::string*>(metadata.varPtr) = config.getString(varName);
        }
      }
    }
  }
};

template <typename T>
std::map<std::string, BindableVariableMetadata> LoadableBehaviorComponent<T>::variableRegistry = {};

template <typename T>
std::vector<std::function<void(LoadableBehaviorComponent<T>*)>> LoadableBehaviorComponent<T>::ConstructorActions = {};

#define BIND(TYPE, VARNAME, COMPONENT_TYPE)                                                       \
  TYPE VARNAME;                                                                                   \
  static void VARNAME##_fn() {                                                                    \
    auto IFILambda = [&]() {                                                                      \
      auto constructorLambda = [&](LoadableBehaviorComponent<COMPONENT_TYPE>* baseObj) {          \
        COMPONENT_TYPE* obj = static_cast<COMPONENT_TYPE*>(baseObj);                              \
        obj->registerBindableVariable(#VARNAME, &(obj->VARNAME), typeid(TYPE));                   \
      };                                                                                          \
                                                                                                  \
      LoadableBehaviorComponent<COMPONENT_TYPE>::ConstructorActions.push_back(constructorLambda); \
    };                                                                                            \
    IFILambda();                                                                                  \
  }

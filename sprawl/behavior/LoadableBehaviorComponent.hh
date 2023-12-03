#include "IBehaviorComponent.hh"
#include "Logging.hh"

// Forward decl
class WADLoader;

template <typename T>
class LoadableBehaviorComponent : public IBehaviorComponent {
 protected:
  LoadableBehaviorComponent<T>() : IBehaviorComponent() { executeConstructorActions(); }
  ~LoadableBehaviorComponent<T>() override { std::cout << "LoadableBehaviorComponent destructor called!" << std::endl; }

  static bool registerBindableVariable(const std::string varName, void* varPtr, const std::type_info& typeInfo) {
    // This method does the actual registration.
    BindableVariableMetadata data = BindableVariableMetadata(varPtr, std::type_index(typeInfo), varName);
    getVariableRegistry().emplace(std::pair<std::string, BindableVariableMetadata>(varName, data));
    LOG_DEBUG_SYS(WADLOADER, "Registered variable {0} of type {1}", varName, typeInfo.name());
    return true;
  }

  // static inline std::map<std::string, BindableVariableMetadata> variableRegistry;
  static inline std::map<std::string, BindableVariableMetadata>& getVariableRegistry() {
    static std::map<std::string, BindableVariableMetadata> registry;
    return registry;
  }

  // static inline std::vector<std::function<void(LoadableBehaviorComponent<T>*)>> ConstructorActions;
  static std::vector<std::function<void(LoadableBehaviorComponent<T>*)>>& getConstructorActions() {
    static std::vector<std::function<void(LoadableBehaviorComponent<T>*)>> actions;
    return actions;
  }

 private:
  friend WADLoader;
  void executeConstructorActions() {
    auto& actions = getConstructorActions();
    LOG_DEBUG_SYS(WADLOADER, "Executing constructor actions.");
    LOG_DEBUG_SYS(WADLOADER, "Constructor actions size (execution time): {0}", actions.size());
    LOG_DEBUG_SYS(WADLOADER, "ConstructorActions addr (execution time): {0}", (void*)&actions);
    for (const auto& action : actions) {
      action(this);
    }
  }

  void initializeBindables(const BehaviorComponentConfig& config) override {
    /*
     * This method takes a bit of explaining. See the README.md in this directory.
     */
    auto& variableRegistry = getVariableRegistry();
    LOG_DEBUG_SYS(WADLOADER, "Executing constructor actions.");
    LOG_DEBUG_SYS(WADLOADER, "Variable registry size: {0}", variableRegistry.size());

    for (const auto& [varName, metadata] : variableRegistry) {
      if (config.hasKey(varName)) {
        LOG_DEBUG_SYS(WADLOADER, "Attempting to load variable: {0}", varName);
        if (metadata.typeIndex == typeid(int)) {
          *static_cast<int*>(metadata.varPtr) = config.getInt(varName);
          LOG_DEBUG_SYS(WADLOADER, "Loaded int variable: {0} = {1}", varName, *static_cast<int*>(metadata.varPtr));
        } else if (metadata.typeIndex == typeid(double)) {
          *static_cast<double*>(metadata.varPtr) = config.getDouble(varName);
          LOG_DEBUG_SYS(WADLOADER, "Loaded double variable: {0} = {1}", varName,
                        *static_cast<double*>(metadata.varPtr));
        } else if (metadata.typeIndex == typeid(std::string)) {
          *static_cast<std::string*>(metadata.varPtr) = config.getString(varName);
          LOG_DEBUG_SYS(WADLOADER, "Loaded string variable: {0} = {1}", varName,
                        *static_cast<std::string*>(metadata.varPtr));
        } else {
          LOG_DEBUG_SYS(WADLOADER, "ERROR: Attempted to load variable {0} of unknown type {1}.", varName,
                        metadata.typeIndex.name());
        }
      }
    }
  }
};

// This version of BIND works by defining a static class that adds the constructor action
// via its constructor - the constructor is executed when the class is initialized, which
// happens at the start of the program because it's declared inline.
#define BIND(TYPE, VARNAME, COMPONENT_TYPE)                                                                          \
  TYPE VARNAME;                                                                                                      \
  class VARNAME##_Init {                                                                                             \
   public:                                                                                                           \
    VARNAME##_Init() {                                                                                               \
      auto constructorLambda = [&](LoadableBehaviorComponent<COMPONENT_TYPE>* baseObj) {                             \
        COMPONENT_TYPE* obj = static_cast<COMPONENT_TYPE*>(baseObj);                                                 \
        obj->registerBindableVariable(#VARNAME, &(obj->VARNAME), typeid(TYPE));                                      \
      };                                                                                                             \
      LoadableBehaviorComponent<COMPONENT_TYPE>::getConstructorActions().push_back(constructorLambda);               \
      LOG_DEBUG_SYS(WADLOADER, "Registered a constructor action: {0}, {1}, {2} ", #COMPONENT_TYPE, #TYPE, #VARNAME); \
      LOG_DEBUG_SYS(WADLOADER, "ConstructorActions addr (registration time): {0}",                                   \
                    (void*)&LoadableBehaviorComponent<COMPONENT_TYPE>::getConstructorActions());                     \
      LOG_DEBUG_SYS(WADLOADER, "Constructor actions size (registration time): {0}", getConstructorActions().size()); \
    }                                                                                                                \
  };                                                                                                                 \
  static inline VARNAME##_Init VARNAME##_init;\

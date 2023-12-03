#include "BehaviorComponentFactory.hh"

// NOTE: A static variable defined in a header file is not a definition of the static variable,
// it's just a declaration. The definition here is what actually allocates the memory for the static variable.
std::unordered_map<std::string, std::function<std::shared_ptr<IBehaviorComponent>()>>
    BehaviorComponentFactory::factories;

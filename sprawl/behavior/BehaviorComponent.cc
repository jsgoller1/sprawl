#include "BehaviorComponent.hh"

#include "Actor.hh"

std::string BehaviorComponent::toString() const {
  return fmt::format("BehaviorComponent({})", this->getOwner()->toString());
}

void BehaviorComponent::initializeBindables(const BehaviorComponentConfig& config) {
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

// NOTE: A static variable defined in a header file is not a definition of the static variable,
// it's just a declaration. The definition here is what actually allocates the memory for the static variable.
std::unordered_map<std::string, BindableVariableMetadata> BehaviorComponent::variableRegistry;

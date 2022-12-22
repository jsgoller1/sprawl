#include "WADLoader.hh"

// Forward decls
class CharacterPhysicsComponent;
class IntegrationWorld;

class IntegrationWADLoader : public WADLoader {
 public:
  IntegrationWADLoader(const FilePath& wadPath);
  ~IntegrationWADLoader() override;
  std::shared_ptr<IntegrationWorld> loadIntegrationWorld() const;

 private:
  std::shared_ptr<CharacterPhysicsComponent> loadCharacterPhysicsComponent(const nlohmann::json& jsonBody) const;
  void loadPlatform(IntegrationWorld& world, const nlohmann::json& jsonBody) const;
  void loadCharacter(IntegrationWorld& world, const nlohmann::json& jsonBody) const;
};

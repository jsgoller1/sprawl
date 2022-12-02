#include "IntegrationWorld.hh"
#include "WADLoader.hh"

class IntegrationWADLoader : public WADLoader {
 public:
  IntegrationWADLoader(const FilePath& wadPath);
  ~IntegrationWADLoader() override;
  std::shared_ptr<IntegrationWorld> loadIntegrationWorld() const;

 private:
  void loadBackground(IntegrationWorld& world, const nlohmann::json& jsonBody) const;
  void loadPlatform(IntegrationWorld& world, const nlohmann::json& jsonBody) const;
  void loadCharacter(IntegrationWorld& world, const nlohmann::json& jsonBody) const;
};

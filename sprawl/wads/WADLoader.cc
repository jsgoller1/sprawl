#include "WADLoader.hh"

#include <fstream>

#include "Background.hh"
#include "Logging.hh"
#include "World.hh"

WADLoader::~WADLoader() = default;

WADLoader::WADLoader(const FilePath& wadDir) {
  std::ifstream wadFile(wadDir + "/wad.json");
  if (!wadFile.is_open()) {
    LOG_FATAL_SYS(WADLOADER, "Could not find wad.json at {0}.", wadDir);
    throw;
  }
  this->_wadDir = wadDir;
  this->_jsonBody = nlohmann::json::parse(wadFile);
}

void WADLoader::loadBackground(World& world, const nlohmann::json& jsonBody) const {
  if (!this->objectEnabled(jsonBody)) {
    return;
  }
  std::shared_ptr<Background> background =
      std::shared_ptr<Background>(new Background(EntityName(jsonBody.value("name", ""))));
  std::shared_ptr<PositionComponent> positionComponent =
      this->loadPositionComponent(background->getIdentity(), jsonBody["position"]);
  background->setPositionComponent(positionComponent);
  std::shared_ptr<DrawingComponent> drawingComponent =
      this->loadDrawingComponent(background->getIdentity(), positionComponent, jsonBody["drawing"]);
  background->setDrawingComponent(drawingComponent);
  world.setBackground(background);
}

bool WADLoader::objectEnabled(const nlohmann::json& jsonBody) const { return jsonBody.value("enabled", false); }

nlohmann::json WADLoader::getJsonBody() const { return this->_jsonBody; }

#include "WADLoader.hh"

#include <fstream>

#include "Logging.hh"

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

bool WADLoader::objectEnabled(const nlohmann::json& jsonBody) const { return jsonBody.value("enabled", false); }

nlohmann::json WADLoader::getJsonBody() const { return this->_jsonBody; }

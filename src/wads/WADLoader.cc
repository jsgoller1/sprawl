#include "WADLoader.hh"

#include "Logging.hh"

bool WADLoader::objectEnabled(const json& jsonBody) const { return jsonBody.value("enabled", false); }

WADLoader::WADLoader(const FilePath& wadDir) {
  std::ifstream wadFile(wadDir + "/wad.json");
  if (!wadFile.is_open()) {
    LOG_FATAL_SYS(WADLOADER, "Could not find wad.json at {0}.", wadDir);
    throw;
  }
  this->_wadDir = wadDir;
  this->_jsonBody = json::parse(wadFile);
}

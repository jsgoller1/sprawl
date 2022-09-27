#include "WADLoader.hh"

shared_ptr<Zone> WADLoader::zoneFromWAD(
    const shared_ptr<FilePath> wadPath) const {
  std::ifstream wadFile(*wadPath);
  json data = json::parse(wadFile);
  shared_ptr<Zone> zone = shared_ptr<Zone>(new Zone());

  // TODO: Add error checking with helpful messages. Pretending for now that
  // WAD files are always correctly structured json
  if (data.contains("background")) {
    this->addBackground(zone, data["background"]);
  }

  // TODO: repeat clauses should be handled outside of add*() functions,
  // but they involve mutating data that each add*() is responsible for;
  // for now, just implementing them as loops inside add*()
  if (data.contains("gameObjects")) {
    for (auto gameObjectJSON : data["gameObjects"]) {
      if (gameObjectJSON["type"] == "Character") {
        this->addCharacter(zone, gameObjectJSON);
      } else if (gameObjectJSON["type"] == "Platform") {
        this->addPlatform(zone, gameObjectJSON);
      } else {
        // TODO: Custom exception indicating we don't know how to create the
        // object. Eventually, we don't need to stop the game over this, but for
        // now we should.
        throw;
      }
    }
  }
  return zone;
}

void WADLoader::addBackground(shared_ptr<Zone> zone,
                              const json& backgroundJSON) const {
  shared_ptr<FilePath> texturePath =
      shared_ptr<FilePath>(new FilePath(backgroundJSON["texturePath"]));
  PositionUnit x = backgroundJSON["position"]["x"];
  PositionUnit y = backgroundJSON["position"]["y"];
  zone->background =
      shared_ptr<Background>(new Background(texturePath, nullptr, x, y));
}

void WADLoader::addCharacter(shared_ptr<Zone> zone,
                             const json& characterJSON) const {
  shared_ptr<GameObjectName> name =
      shared_ptr<GameObjectName>(new GameObjectName(characterJSON["name"]));
  shared_ptr<FilePath> texturePath =
      shared_ptr<FilePath>(new FilePath(characterJSON["texturePath"]));
  PositionUnit x = characterJSON["position"]["x"];
  PositionUnit y = characterJSON["position"]["y"];
  shared_ptr<Point> center = shared_ptr<Point>(new Point{.x = x, .y = y});

  CharacterSPtr character =
      CharacterSPtr(new Character(center, name, nullptr, texturePath));
  character->inferBoundingBoxFromTexture();
  zone->physicsMgr->manageComponent(character->getPhysicsComponent());

  if (*name == "Player") {
    zone->player = character;
  } else {
    zone->gameObjects->push_back(character);
  }
}
void WADLoader::addPlatform(shared_ptr<Zone> zone,
                            const json& platformJSON) const {
  int repeatCount = 1;
  PositionUnit xOffset = 0;
  PositionUnit yOffset = 0;
  if (platformJSON.contains("repeat")) {
    repeatCount = platformJSON["repeat"]["count"];
    if (platformJSON["repeat"].contains("xOffset")) {
      xOffset = platformJSON["repeat"]["xOffset"];
    }
    if (platformJSON["repeat"].contains("yOffset")) {
      yOffset = platformJSON["repeat"]["yOffset"];
    }
  }

  PositionUnit x = platformJSON["position"]["x"];
  PositionUnit y = platformJSON["position"]["y"];
  for (int count = 0; count < repeatCount; count++) {
    shared_ptr<Point> center = shared_ptr<Point>(new Point{.x = x, .y = y});
    shared_ptr<FilePath> texturePath =
        shared_ptr<FilePath>(new FilePath(platformJSON["texturePath"]));
    shared_ptr<Platform> platform = shared_ptr<Platform>(
        new Platform(center, nullptr, nullptr, texturePath));
    platform->inferBoundingBoxFromTexture();
    zone->physicsMgr->manageComponent(platform->getPhysicsComponent());
    zone->gameObjects->push_back(platform);
    x += xOffset;
    y += yOffset;
  }
}

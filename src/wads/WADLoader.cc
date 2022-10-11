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
      if (gameObjectJSON["enabled"] == "false") {
        continue;
      }
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
  shared_ptr<Background> background = shared_ptr<Background>(new Background());
  shared_ptr<EntityName> name =
      shared_ptr<EntityName>(new EntityName(backgroundJSON["name"]));
  background->setName(name);

  // Initialize position
  XCoord x = backgroundJSON["position"]["x"];
  YCoord y = backgroundJSON["position"]["y"];
  background->getPositionComponent()->setX(x);
  background->getPositionComponent()->setY(y);

  // Load texture
  shared_ptr<FilePath> texturePath =
      shared_ptr<FilePath>(new FilePath(backgroundJSON["texturePath"]));
  shared_ptr<Texture> texture = shared_ptr<Texture>(new Texture(texturePath));
  background->getDrawingComponent()->setTexture(texture);

  zone->setBackground(background);
}

void WADLoader::addCharacter(shared_ptr<Zone> zone,
                             const json& characterJSON) const {
  shared_ptr<Character> character = shared_ptr<Character>(new Character());
  shared_ptr<EntityName> name =
      shared_ptr<EntityName>(new EntityName(characterJSON["name"]));
  character->setName(name);

  // Initialize position
  XCoord x = characterJSON["position"]["x"];
  YCoord y = characterJSON["position"]["y"];
  character->getPositionComponent()->setX(x);
  character->getPositionComponent()->setY(y);

  // Load texture
  shared_ptr<FilePath> texturePath =
      shared_ptr<FilePath>(new FilePath(characterJSON["texturePath"]));
  shared_ptr<Texture> texture = shared_ptr<Texture>(new Texture(texturePath));
  character->getDrawingComponent()->setTexture(texture);
  character->inferBoundingBoxFromTexture();

  (characterJSON["isPlayerCharacter"] == "true")
      ? zone->addPlayerCharacter(character)
      : zone->addGameObject(character);
}
void WADLoader::addPlatform(shared_ptr<Zone> zone,
                            const json& platformJSON) const {
  // TODO: This repetition logic should go someplace else so it can be applied
  // to any object
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

  shared_ptr<Platform> platform;
  shared_ptr<EntityName> name;
  for (int count = 0; count < repeatCount; count++) {
    platform = shared_ptr<Platform>(new Platform());
    name = shared_ptr<EntityName>(new EntityName(platformJSON["name"]));
    platform->getPositionComponent()->setX(x);
    platform->getPositionComponent()->setY(y);

    shared_ptr<FilePath> texturePath =
        shared_ptr<FilePath>(new FilePath(platformJSON["texturePath"]));
    shared_ptr<Texture> texture = shared_ptr<Texture>(new Texture(texturePath));
    platform->getDrawingComponent()->setTexture(texture);
    platform->inferBoundingBoxFromTexture();

    zone->addGameObject(platform);

    x += xOffset;
    y += yOffset;
  }
}

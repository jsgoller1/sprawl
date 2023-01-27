#include "WallCollection.hh"

#include "Wall.hh"

WallCollection::WallCollection(const std::vector<int> internalWallIndices, const LevelSpriteManager& levelSpriteManager,
                               DrawingProxy& drawingProxy)
    : _walls(std::vector<std::unique_ptr<Wall>>()) {
  //  TODO: Every level should always have border walls; for now though, we want to draw every wall.
  // This function should probably be responsible for the random layout, but not "how to draw walls"
  for (int i : HORIZONTAL_BORDER_WALLS) {
    this->_walls.push_back(std::unique_ptr<Wall>(new Wall(i, levelSpriteManager, drawingProxy)));
  }
  for (int i : VERTICAL_BORDER_WALLS) {
    this->_walls.push_back(std::unique_ptr<Wall>(new Wall(i, levelSpriteManager, drawingProxy)));
  }
  for (int i : internalWallIndices) {
    this->_walls.push_back(std::unique_ptr<Wall>(new Wall(i, levelSpriteManager, drawingProxy)));
  }
}
Wall* WallCollection::get(const size_t index) { return this->_walls.at(index).get(); }
size_t WallCollection::size() { return this->_walls.size(); }

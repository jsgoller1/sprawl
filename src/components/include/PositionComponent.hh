#pragma once
#include "Memory.hh"
#include "Types.hh"

typedef struct Point {
  PositionUnit x;
  PositionUnit y;
} Point;

class PositionComponent {
 public:
  PositionComponent(const PositionUnit x, const PositionUnit y) : x(x), y(y) {}
  PositionComponent(shared_ptr<Point> center);

  PositionUnit getX() const { return this->x; }
  void setX(const PositionUnit x) { this->x = x; }
  PositionUnit getY() const { return this->y; }
  void setY(const PositionUnit y) { this->y = y; }

  shared_ptr<Point> getCenter();
  void setCenter(shared_ptr<Point> center);
  void updateX(const PositionUnit x);
  void updateY(const PositionUnit y);
  void updateCenter(shared_ptr<Point> delta);
  void move(const shared_ptr<Point> movement);

 private:
  PositionUnit x;
  PositionUnit y;
};

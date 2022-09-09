typedef int PositionUnit;

typedef struct Position {
  PositionUnit x;
  PositionUnit y;
} Position;

class PositionManager {
 public:
  void setPosition();
  Position getPosition();
  Position move();
};

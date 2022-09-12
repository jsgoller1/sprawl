#include "Memory.hh"

typedef int PositionUnit;

typedef struct Position {
  PositionUnit x;
  PositionUnit y;
} Position;

class PositionMgr {
 public:
  void setPosition();
  Position getPosition();
  Position move();
};

typedef unique_ptr<PositionMgr> PositionMgrSPtr;

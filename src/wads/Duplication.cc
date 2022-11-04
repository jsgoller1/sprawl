#include "Duplication.hh"

DuplicationBehavior::DuplicationBehavior(const nlohmann::json& jsonBody) {
  this->_curr = 0;
  this->_count = jsonBody.value("count", 1);
  this->_xOffset = jsonBody.value("xOffset", 0);
  this->_yOffset = jsonBody.value("yOffset", 0);
}

Vect2D DuplicationBehavior::getOffset() { return Vect2D(this->_xOffset, this->_yOffset); }
PositionUnit DuplicationBehavior::getXOffset() { return this->_xOffset; }
PositionUnit DuplicationBehavior::getYOffset() { return this->_yOffset; }
int DuplicationBehavior::getCount() { return this->_count; }
int DuplicationBehavior::getCurr() { return this->_curr; }

void DuplicationBehavior::next() { this->_curr++; }
bool DuplicationBehavior::done() const { return this->_curr == this->_count; }

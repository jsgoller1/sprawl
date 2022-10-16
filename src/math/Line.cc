#include "Line.hh"

Line::Line(const shared_ptr<Vect2D> p1, const shared_ptr<Vect2D> p2) {}
Line::Line(const shared_ptr<Line> line) {}

shared_ptr<Vect2D> Line::getSlope() const {}
shared_ptr<Vect2D> Line::getLength() const {}
shared_ptr<pair<shared_ptr<Vect2D>, shared_ptr<Vect2D>>> Line::getPoints()
    const {}
